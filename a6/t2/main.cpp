#include <boost/asio.hpp>
#include <iostream>

using namespace std;
using namespace boost::asio::ip;

class WebServer {
private:
  class Connection {
  public:
    tcp::socket socket;
    Connection(boost::asio::io_service &io_service) : socket(io_service) {}
  };

  boost::asio::io_service io_service;

  tcp::endpoint endpoint;
  tcp::acceptor acceptor;
  char delim = ' ';

  void serve_root(ostream &buf){
      buf << "HTTP/1.1 200 OK\r\n";
      buf << "Content-Type: text/html; charset=utf-8\r\n\r\n";
      buf << "<html><body>";
      buf << "Dette er hovedsiden";
      buf << "</html></body>\r\n";
  }

  void serve_page(ostream &buf){
      buf << "HTTP/1.1 200 OK\r\n";
      buf << "Content-Type: text/html; charset=utf-8\r\n\r\n";
      buf << "<html><body>";
      buf << "Dette er en side";
      buf << "</html></body>\r\n";
  }

  void serve_404(ostream &buf){
      buf << "HTTP/1.1 404 Not Found\r\n";
      buf << "Content-Type: text/html; charset=utf-8\r\n\r\n";
      buf << "<html><body>";
      buf << "404 Page not found";
      buf << "</html></body>\r\n";
  }

  void handle_request(shared_ptr<Connection> connection) {
    auto read_buffer = make_shared<boost::asio::streambuf>();
    async_read_until(connection->socket, *read_buffer, "\r\n\r\n", [this, connection, read_buffer] (const boost::system::error_code &ec, size_t) {
      // If not error:
      if (ec) {
        return;
      }

      // Retrieve message from client as string:
      istream read_stream(read_buffer.get());
      std::string header;

      getline(read_stream, header); // get first request line

      // get the request path
      size_t first_pos = header.find(delim);
      size_t second_pos = header.find(delim, first_pos+1);
      std::string path = header.substr(first_pos+1, (second_pos-first_pos-1));

      auto write_buffer = make_shared<boost::asio::streambuf>();
      ostream write_stream(write_buffer.get());

      // serve content based on request path
      if(path == "/") serve_root(write_stream);
      else if(path == "/en_side") serve_page(write_stream);
      else serve_404(write_stream);

      // Write to client
      async_write(connection->socket, *write_buffer, [this, connection, write_buffer] (const boost::system::error_code &ec, size_t) {});
    });
  }

  void accept() {
    // The (client) connection is added to the lambda parameter and handle_request
    // in order to keep the object alive for as long as it is needed.
    auto connection = make_shared<Connection>(io_service);
    
    // Accepts a new (client) connection. On connection, immediately start accepting a new connection 
    acceptor.async_accept(connection->socket, [this, connection](const boost::system::error_code &ec) {
      accept();
      // If not error:
      if (!ec) {
        handle_request(connection);
      }
    });
  }

public:
  WebServer() : endpoint(tcp::v4(), 9988), acceptor(io_service, endpoint) {}

  void start() {
    accept();

    io_service.run();
  }
};

int main() {
  WebServer web_server;
  cout << "starting webserver at :9988" << endl;
  web_server.start();
}

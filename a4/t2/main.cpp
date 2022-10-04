#include <gtkmm.h>

class Window : public Gtk::Window {
 public:
  Gtk::VBox vbox;
  Gtk::Entry entry_first;
  Gtk::Entry entry_last;
  Gtk::Button button;
  Gtk::Label label;

  Window() {
    button.set_label("Combine names");
    button.set_sensitive(FALSE);
    vbox.pack_start(entry_first);
    vbox.pack_start(entry_last);
    vbox.pack_start(button);
    vbox.pack_start(label);

    add(vbox);
    show_all();

    entry_first.signal_changed().connect([this]() {
      button.set_sensitive(entry_first.get_text_length() && entry_last.get_text_length());
    });

    entry_last.signal_changed().connect([this]() {
      button.set_sensitive(entry_first.get_text_length() && entry_last.get_text_length());
    });

    button.signal_clicked().connect([this]() {
      label.set_text("Name: " + entry_first.get_text() + " " + entry_last.get_text());
    });
  }
};

int main() {
  Gtk::Main gtk_main;
  Window window;
  window.set_title("øving 4");
  gtk_main.run(window);
}

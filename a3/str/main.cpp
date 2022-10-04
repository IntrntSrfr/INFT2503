#include <iostream>
#include <string>

int main(){
  // a
  std::cout << "input 3 words" << '\n';
  std::string word1, word2, word3;
  std::cin >> word1;
  std::cin >> word2;
  std::cin >> word3;
  std::cout << '\n';

  // b
  std::string sentence = word1 + " " + word2 + " " + word3 + ".";
  
  // c
  std::cout << "length of '" << word1 << "': " << word1.length() << '\n';
  std::cout << "length of '" << word2 << "': " << word2.length() << '\n';
  std::cout << "length of '" << word3 << "': " << word3.length() << '\n';
  std::cout << "length of '" << sentence << "': " << sentence.length() << "\n\n";

  // d
  std::string sentence2 = sentence;

  // e
  if(sentence2.length() > 11) { 
    sentence2[9] = 'x';
    sentence2[11] = 'x';
    std::cout << sentence << '\n';
    std::cout << sentence2 << "\n\n";
  }

  // f
  if(sentence.length() > 5){
    std::string sentence_start = sentence.substr(0, 5);
    std::cout << sentence << '\n';
    std::cout << sentence_start << "\n\n";
  }

  // g
  if(sentence.find("hallo") != std::string::npos){
    std::cout << "sentence contains 'hallo'" << "\n\n";
  }else{
    std::cout << "sentence does not contain 'hallo'" << "\n\n";
  }

  // h
  int index = 0;
  while(true){
    index = sentence.find("er", index);
    if(index== std::string::npos) break;
    std::cout << "found 'er' at index " << index << '\n';
    index += 2;
  }

  return 0;
}

#include<fstream>
#include<string>

#define EXT 4
#define INFO_LENGTH 160
#define OFFSET 8		// for * FILE: 
class Generator{

protected:
  std::ofstream m_writer;
  const std::string m_fileName;
  short int m_type;
  enum{
    TYPE_C,
    TYPE_CPP,
    TYPE_H,
    TYPE_HPP,
    OTHERS
  };
public:
  Generator(std::string flNm );
  void parseFileName();
  void startPrinting();
protected:
  void convert2compilerGuard(std::string flNm);
  void printTemplate();
  void writeClassName();
};
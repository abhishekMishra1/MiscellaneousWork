#include"generator.hpp"
#include<cctype>
#include<iostream>

Generator::Generator(const std::string flNm ):m_fileName(flNm),m_type(OTHERS){
  m_writer.open(flNm.c_str());
}

void Generator::parseFileName(){
  int i;
  if(m_writer.is_open()){
    for(i = 0;i<m_fileName.size();i++){
      if(m_fileName[i] == '.')
	break;
    }
    /*There can be following cases
     * 1. cpp
     * 2. hpp
     * 3. c
     * 4. h
     *
     * Also, for other cases, we should reject.
     * So, now we have something XXXX.xxx OR XXXXX.x OR XXXX.xxxx etc.
     */
  if(m_fileName[i+1] == 'c' && m_fileName[i+2] == '\0')	//Now we know that it is a c source file
    m_type = TYPE_C;
  else if(m_fileName[i+1] == 'c' && m_fileName[i+2] == 'p' && 
    m_fileName[i+3] == 'p' && m_fileName[i+4] == '\0') 	// This is c++ source file
    m_type = TYPE_CPP;
  else if(m_fileName[i+1] == 'h' && m_fileName[i+2] == '\0')	//Now we know that it is a c/c++ header file
    m_type = TYPE_H;
  else if(m_fileName[i+1] == 'h' && m_fileName[i+2] == 'p' && 
    m_fileName[i+3] == 'p' && m_fileName[i+4] == '\0') 	// This is c++ header file
    m_type = TYPE_HPP;
  else
    m_type = OTHERS;
  }
  else
    std::cout<<"Cannot open the newly created file for priting..\n";
}

void Generator::startPrinting(){
  printTemplate();
  switch(m_type){
    case TYPE_C:
      m_writer<<"#include<stdio.h>\n\nint main(){\n\nreturn 0;\n}\n";
      break;

    case TYPE_CPP:
      m_writer<<"#include<iostream>\n\nusing namespace std;\n\n\int main(){\n\nreturn 0;\n}\n";
      break;
    case TYPE_H:
    case TYPE_HPP:
      m_writer<<"#ifndef _";
      convert2compilerGuard(m_fileName);
      m_writer<<"_\n#define _";
      convert2compilerGuard(m_fileName);
      m_writer<<"_\nclass ";
      writeClassName();
      m_writer<<"{\npublic:\n\nprivate:\n\nprotected\n\n};\n\n#endif\n";
      break;
    case OTHERS:
      std::cout<<"No matching type file name. File name can be\n1. XXXX.cpp\n2. XXXX.c\n3. XXXX.h\n4. XXXX.hpp\n";
      break;
    default:
      std::cout<<"How you dare to print me on screen. You have screwed your code\n";
      break;
  }
  m_writer.flush();
}

void Generator::convert2compilerGuard(std::string flNm){
  char ch;
  //std::cout<<flNm<<std::endl;
  for(int i = 0; i < flNm.size(); i++){
    //check the range for lower case
    ch = flNm[i];
    if(islower(ch)){
	ch = toupper(ch);
	m_writer<<ch;
	//std::cout<<ch;
    }
    else if(ch == '.'){
	m_writer<<"_";
    }
  }
 // std::cout<<std::endl;
  
}


void Generator::printTemplate(){
  int i;
// We need to print following format
    /***********************************
    * FILE: XXXX.xxx                   *
    * DESC:                            *
    * AUTH:                            *
    ***********************************/

  //For 1st line  
  m_writer<<'/';
  for(i = 0; i<INFO_LENGTH-1; i++)
    m_writer<<'*';
    
  //For 2nd line & part of 3rd line
  m_writer<<"\n* FILE: "<<m_fileName;
  for(i=0;i<INFO_LENGTH-OFFSET-m_fileName.size()-1;i++)
    m_writer<<' ';
  m_writer<<"*\n* DESC: ";
  
  //For 3rd and part of 4th line
  for(i=0;i<INFO_LENGTH-OFFSET-1;i++)
    m_writer<<" ";
  m_writer<<"*\n* AUTH: ";

  //For 4th line
  for(i=0;i<INFO_LENGTH-OFFSET-1;i++)
    m_writer<<" ";
  m_writer<<"*\n";
  
  //For 5th line
  for(i = 0; i<INFO_LENGTH-1; i++)
    m_writer<<'*';
  m_writer<<"/\n\n\n";

  m_writer.flush();
}


void Generator::writeClassName(){
  char ch = m_fileName.at(0);
  ch = toupper(ch);
  m_writer<<ch;
  for(int i = 1; i <m_fileName.size();i++){
    ch = m_fileName[i];
    if('.' == ch)
      break;
    m_writer<<ch;
  }
}
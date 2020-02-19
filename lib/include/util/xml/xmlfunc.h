#ifndef __XMLFUNC_H__
#define __XMLFUNC_H__

#include <iostream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "util/xml/tinyxml/tinystr.h"
#include "util/xml/tinyxml/tinyxml.h"

#ifdef __cplusplus
extern "C" {
#endif

bool LoadXML(std::string XmlFile, TiXmlDocument *&pDoc);
void SaveXML(std::string &outPathName, TiXmlDocument *&pDoc);

bool DelNode(std::string XmlFile, std::string &outPathName, std::string strNodeName);
bool QueryNode_Text(std::string XmlFile, std::string strNodeName, std::string &strText);
bool ModifyNode_Text(TiXmlDocument *&pDoc, std::string strNodeName, std::string strText);
bool AddNode_Text(TiXmlDocument *&pDoc, std::string strParNodeName, std::string strNodeName, std::string strText);
bool InsertNode_Text(TiXmlDocument *&pDoc,
                     std::string strParNodeName,
                     std::string strPrevNodeName,
                     std::string strNodeName,
                     std::string strText);

bool ModifyNode_TextEx(TiXmlDocument *&pDoc, std::string strNodeName, std::string strText);
bool QueryNode_TextEx(std::string XmlFile, std::string strNodeName, std::string &strText);

bool QueryNode_TextEx2(std::string XmlFile, std::string strNodeName, std::string &strText, int &index);

void SaveTxtFile(std::string &str, int idx, int count);

//void finddir(const char * lpPath, std::vector<std::string>& filelist, int dir, int subdir);

#ifdef __cplusplus
}
#endif

#endif
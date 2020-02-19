
#include <iostream>
#include "util/xml/tinyxml/tinyxml.h"
#include "util/xml/tinyxml/tinystr.h"
#include <string>
//#include <windows.h>
//#include <atlstr.h>

#include <vector>

#include <fstream>

#include "util/xml/xmlfunc.h"

using namespace std;

static int idx = 1;
#if 0
static void finddir(const char * lpPath, vector<string>& filelist, int dir, int subdir)
{
    char szFind[MAX_PATH];
    char szFile[MAX_PATH];
    WIN32_FIND_DATA FindFileData;
    strcpy_s(szFind,lpPath);
    strcat_s(szFind,"*.*");
    HANDLE hFind=::FindFirstFile(szFind,&FindFileData);

    if(INVALID_HANDLE_VALUE == hFind) return;

    while(TRUE)
    {
        if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if(FindFileData.cFileName[0] != '.')
            {
                if(dir) filelist.push_back(FindFileData.cFileName);

                strcpy_s(szFile, lpPath);
                strcat_s(szFile, "");
                strcat_s(szFile, FindFileData.cFileName);              

                if(subdir) finddir(szFile, filelist,0,0);
            }
        }
        else
        {
            if (!dir) filelist.push_back(FindFileData.cFileName);            
            //cout << FindFileData.cFileName << endl;
        }

        if(!FindNextFile(hFind,&FindFileData)) break;
    }

    FindClose(hFind);
}
#endif
/*! 
*  /brief ͨ�����ڵ�ͽڵ�����ȡ�ڵ�ָ�롣 
* 
*  /param pRootEle   xml�ļ��ĸ��ڵ㡣 
*  /param strNodeName  Ҫ��ѯ�Ľڵ��� 
*  /param Node      ��Ҫ��ѯ�Ľڵ�ָ�� 
*  /return �Ƿ��ҵ���trueΪ�ҵ���Ӧ�ڵ�ָ�룬false��ʾû���ҵ���Ӧ�ڵ�ָ�롣 
*/
static bool GetNodePointerByName(TiXmlElement *pRootEle, std::string &strNodeName, TiXmlElement *&Node) {
  // ������ڸ��ڵ��������˳�
  if (strNodeName == pRootEle->Value()) {
    Node = pRootEle;
    return true;
  }
  TiXmlElement *pEle = pRootEle;
  for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement()) {
    //�ݹ鴦���ӽڵ㣬��ȡ�ڵ�ָ��
    if (GetNodePointerByName(pEle, strNodeName, Node))
      return true;
  }
  return false;
}

/*! 
*  /brief ͨ�����ڵ�ͽڵ�����ȡ�ڵ�ָ�롣 
* 
*  /param pRootEle   xml�ļ��ĸ��ڵ㡣 
*  /param strNodeName  Ҫ��ѯ�Ľڵ��� 
*  /param Node      ��Ҫ��ѯ�Ľڵ�ָ�� 
*  /return �Ƿ��ҵ���trueΪ�ҵ���Ӧ�ڵ�ָ�룬false��ʾû���ҵ���Ӧ�ڵ�ָ�롣
*  /idx   ���ҵڼ�����based on 0 
*/
static bool GetNodePointerByNameEx(TiXmlElement *pRootEle, std::string &strNodeName, TiXmlElement *&Node) {

  // ������ڸ��ڵ��������˳�
  if (strNodeName == pRootEle->Value()) {
    if (idx) {
      idx--;
    } else {
      Node = pRootEle;
      return true;
    }
  }

  TiXmlElement *pEle = pRootEle;
  for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement()) {
    //�ݹ鴦���ӽڵ㣬��ȡ�ڵ�ָ��
    if (GetNodePointerByNameEx(pEle, strNodeName, Node))
      return true;
  }
  return false;
}

static bool GetNodePointerByNameEx2(TiXmlElement *pRootEle, std::string &strNodeName, TiXmlElement *&Node, int &index) {

  // ������ڸ��ڵ��������˳�
  if (strNodeName == pRootEle->Value()) {
    if (index) {
      index--;
    } else {
      Node = pRootEle;
      return true;
    }
  }

  TiXmlElement *pEle = pRootEle;
  for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement()) {
    //�ݹ鴦���ӽڵ㣬��ȡ�ڵ�ָ��
    if (GetNodePointerByNameEx2(pEle, strNodeName, Node, index))
      return true;
  }
  return false;
}

/*! 
*  /brief ɾ��ָ���ڵ��ֵ�� 
* 
*  /param XmlFile xml�ļ�ȫ·���� 
*  /param strNodeName ָ���Ľڵ����� 
*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
*/
bool DelNode(std::string XmlFile, string &outPathName, std::string strNodeName) {
  // ����һ��TiXmlDocument��ָ��
  TiXmlDocument *pDoc = new TiXmlDocument();
  if (NULL == pDoc) {
    return false;
  }
  pDoc->LoadFile(XmlFile);
  TiXmlElement *pRootEle = pDoc->RootElement();
  if (NULL == pRootEle) {
    return false;
  }
  TiXmlElement *pNode = NULL;
  GetNodePointerByName(pRootEle, strNodeName, pNode);
  // �����Ǹ��ڵ�
  if (pRootEle == pNode) {
    if (pDoc->RemoveChild(pRootEle)) {
      pDoc->SaveFile(outPathName);
      return true;
    } else
      return false;
  }
  // �����������ڵ�
  if (NULL != pNode) {
    TiXmlNode *pParNode = pNode->Parent();
    if (NULL == pParNode) {
      return false;
    }

    TiXmlElement *pParentEle = pParNode->ToElement();
    if (NULL != pParentEle) {
      if (pParentEle->RemoveChild(pNode))
        pDoc->SaveFile(outPathName);
      else
        return false;
    }
  } else {
    return false;
  }
  return false;
}

/*! 
*  /brief ͨ���ڵ��ѯ�� 
* 
*  /param XmlFile   xml�ļ�ȫ·���� 
*  /param strNodeName  Ҫ��ѯ�Ľڵ��� 
*  /param strText      Ҫ��ѯ�Ľڵ��ı� 
*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
*/
bool QueryNode_Text(std::string XmlFile, std::string strNodeName, std::string &strText) {
  // ����һ��TiXmlDocument��ָ��
  TiXmlDocument *pDoc = new TiXmlDocument();
  if (NULL == pDoc) {
    delete pDoc;
    return false;
  }
  pDoc->LoadFile(XmlFile);
  TiXmlElement *pRootEle = pDoc->RootElement();
  if (NULL == pRootEle) {
    delete pDoc;
    return false;
  }
  TiXmlElement *pNode = NULL;
  GetNodePointerByName(pRootEle, strNodeName, pNode);
  if (NULL != pNode) {
    strText = pNode->GetText();
    delete pDoc;
    return true;
  } else {
    delete pDoc;
    return false;
  }

}

/*! 
*  /brief ͨ���ڵ��ѯ�� 
* 
*  /param XmlFile   xml�ļ�ȫ·���� 
*  /param strNodeName  Ҫ��ѯ�Ľڵ��� 
*  /param strText      Ҫ��ѯ�Ľڵ��ı� 
*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
*/
bool QueryNode_TextEx(std::string XmlFile, std::string strNodeName, std::string &strText) {
  // ����һ��TiXmlDocument��ָ��
  TiXmlDocument *pDoc = new TiXmlDocument();
  if (NULL == pDoc) {
    return false;
  }
  pDoc->LoadFile(XmlFile);
  TiXmlElement *pRootEle = pDoc->RootElement();
  if (NULL == pRootEle) {
    return false;
  }

  idx = 1;
  TiXmlElement *pNode = NULL;
  GetNodePointerByNameEx(pRootEle, strNodeName, pNode);
  if (NULL != pNode) {
    strText = pNode->GetText();
    return true;
  } else {
    return false;
  }

}

/*! 
*  /brief ͨ���ڵ��ѯ�� 
* 
*  /param XmlFile   xml�ļ�ȫ·���� 
*  /param strNodeName  Ҫ��ѯ�Ľڵ��� 
*  /param strText      Ҫ��ѯ�Ľڵ��ı� 
*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
*/
bool QueryNode_TextEx2(std::string XmlFile, std::string strNodeName, std::string &strText, int &index) {
  // ����һ��TiXmlDocument��ָ��
  TiXmlDocument *pDoc = new TiXmlDocument();
  if (NULL == pDoc) {
    return false;
  }
  pDoc->LoadFile(XmlFile);
  TiXmlElement *pRootEle = pDoc->RootElement();
  if (NULL == pRootEle) {
    return false;
  }

  //idx = 1;
  TiXmlElement *pNode = NULL;
  GetNodePointerByNameEx2(pRootEle, strNodeName, pNode, index);
  if (NULL != pNode) {
    strText = pNode->GetText();
    return true;
  } else {
    return false;
  }

}

/*! 
*  /brief �޸�ָ���ڵ���ı��� 
* 
*  /param XmlFile xml�ļ�ȫ·���� 
*  /param strNodeName ָ���Ľڵ����� 
*  /param strText �����趨���ı���ֵ 
*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
*/
bool ModifyNode_Text(TiXmlDocument *&pDoc, std::string strNodeName, std::string strText) {
  // ����һ��TiXmlDocument��ָ��
#if 0
  TiXmlDocument *pDoc = new TiXmlDocument();
  if (NULL==pDoc)
  {
      return false;
  }
  pDoc->LoadFile(XmlFile);
#endif
  TiXmlElement *pRootEle = pDoc->RootElement();
  if (NULL == pRootEle) {
    return false;
  }

  TiXmlElement *pNode = NULL;
  GetNodePointerByName(pRootEle, strNodeName, pNode);
  if (NULL != pNode) {
    pNode->Clear();  // ������������ı�
    // Ȼ������ı��������ļ�
    TiXmlText *pValue = new TiXmlText(strText);
    pNode->LinkEndChild(pValue);
    //pDoc->SaveFile(outPathName);
    return true;
  } else
    return false;
}

/*! 
*  /brief �޸�ָ���ڵ���ı��� 
* 
*  /param XmlFile xml�ļ�ȫ·���� 
*  /param strNodeName ָ���Ľڵ����� 
*  /param strText �����趨���ı���ֵ 
*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ�
*  /idx   ���ҵڼ�����based on 0 
*/
bool ModifyNode_TextEx(TiXmlDocument *&pDoc, std::string strNodeName, std::string strText) {
  // ����һ��TiXmlDocument��ָ��
#if 0
  TiXmlDocument *pDoc = new TiXmlDocument();
  if (NULL==pDoc)
  {
      return false;
  }
  pDoc->LoadFile(XmlFile);
#endif
  TiXmlElement *pRootEle = pDoc->RootElement();
  if (NULL == pRootEle) {
    return false;
  }

  idx = 1;
  TiXmlElement *pNode = NULL;
  GetNodePointerByNameEx(pRootEle, strNodeName, pNode);
  if (NULL != pNode) {
    pNode->Clear();  // ������������ı�
    // Ȼ������ı��������ļ�
    TiXmlText *pValue = new TiXmlText(strText);
    pNode->LinkEndChild(pValue);
    //pDoc->SaveFile(outPathName);
    return true;
  } else
    return false;
}

/*!
*  /brief ����ָ���ڵ���ı��� 
* 
*  /param XmlFile xml�ļ�ȫ·���� 
*  /param strParNodeName Ҫ���ӵĽڵ�ĸ��ڵ㡣 
*  /param strNodeName ָ���Ľڵ����� 
*  /param strText Ҫ���ӵ��ı� 
*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
*/
bool AddNode_Text(TiXmlDocument *&pDoc, std::string strParNodeName, std::string strNodeName, std::string strText) {
#if 0
  // ����һ��TiXmlDocument��ָ��
  TiXmlDocument *pDoc = new TiXmlDocument();
  if (NULL==pDoc)
  {
      return false;
  }
  pDoc->LoadFile(XmlFile);
#endif
  TiXmlElement *pRootEle = pDoc->RootElement();
  if (NULL == pRootEle) {
    return false;
  }

  TiXmlElement *pNode = NULL;
  GetNodePointerByName(pRootEle, strParNodeName, pNode);
  if (NULL != pNode) {
    // �����ӽڵ㣺pNewNode
    TiXmlElement *pNewNode = new TiXmlElement(strNodeName);
    if (NULL == pNewNode) {
      return false;
    }
    // ���ýڵ��ı���Ȼ�����ڵ�
    TiXmlText *pNewValue = new TiXmlText(strText);
    pNewNode->LinkEndChild(pNewValue);
    pNode->InsertEndChild(*pNewNode);
    //pDoc->SaveFile(outPathName);
    return true;
  } else
    return false;

}

bool InsertNode_Text(TiXmlDocument *&pDoc,
                     std::string strParNodeName,
                     std::string strPrevNodeName,
                     std::string strNodeName,
                     std::string strText) {
#if 0
  // ����һ��TiXmlDocument��ָ��
  TiXmlDocument *pDoc = new TiXmlDocument();
  if (NULL==pDoc)
  {
      return false;
  }
  pDoc->LoadFile(XmlFile);
#endif
  TiXmlElement *pRootEle = pDoc->RootElement();
  if (NULL == pRootEle) {
    return false;
  }

  TiXmlElement *pNode = NULL;
  GetNodePointerByName(pRootEle, strParNodeName, pNode);

  TiXmlElement *pPrevNode = NULL;
  GetNodePointerByName(pRootEle, strPrevNodeName, pPrevNode);
  if (NULL != pNode) {
    // �����ӽڵ㣺pNewNode
    TiXmlElement *pNewNode = new TiXmlElement(strNodeName);
    if (NULL == pNewNode) {
      return false;
    }
    // ���ýڵ��ı���Ȼ�����ڵ�
    TiXmlText *pNewValue = new TiXmlText(strText);
    pNewNode->LinkEndChild(pNewValue);
    //pNode->InsertEndChild(*pNewNode);
    pNode->InsertAfterChild(pPrevNode, *pNewNode);
    //pDoc->SaveFile(outPathName);
    return true;
  } else
    return false;

}

bool LoadXML(std::string XmlFile, TiXmlDocument *&pDoc) {
  // ����һ��TiXmlDocument��ָ��
  pDoc = new TiXmlDocument();
  if (NULL == pDoc) {
    return false;
  }
  pDoc->LoadFile(XmlFile);

  return true;
}

void SaveXML(string &outPathName, TiXmlDocument *&pDoc) {
  pDoc->SaveFile(outPathName);
}
/*
void SaveTxtFile(string& str, int idx, int count)
{
    //Save File
    //                            trainval=train+val
    //<------------------------------------------------------------->
    //|------------------------------------------|------------------|-----------|
    //                   train                          val=100       test=50
    
    int num  = count/3;  // count - 150
    int numx2= num*2;    // count - 50

    if( idx < numx2 ) trainval_file << str << endl;
    if( idx >= numx2 ) test_file << str << endl;
    if( idx < num ) train_file << str << endl;
    if( idx >=num && idx < numx2 ) val_file << str << endl;
}
*/


#if 0
int main()
{
#define NUM  30//80

    string inDirPrefix = "E:\\cnn-dataset\\imagenet2012\\ILSVRC2012_bbox_train_v2\\";

    string outDir = "F:\\job\\FR\\myXML\\myXML\\myXML\\data\\out\\";

    //string inDirName[NUM] = 
    //{
    //    "n01667778\\",
    //    "n01695060\\",
    //    "n01770393\\",
    //    "n01784675\\",
    //    "n01944390\\",
    //    "n01984695\\",
    //    "n02056570\\",
    //    "n02108551\\",
    //    "n02134084\\",
    //    "n02236044\\",
    //    "n02317335\\",
    //    "n02342885\\",
    //    "n02395406\\",
    //    "n02669723\\",
    //    "n02687172\\",
    //    "n02692877\\",
    //    "n02730930\\",
    //    "n02769748\\",
    //    "n02790996\\",
    //    "n02802426\\",
    //    "n02808440\\",
    //    "n02837789\\",
    //    "n02883205\\",
    //    "n02892767\\",
    //    "n02906734\\",
    //    "n02948072\\",
    //    "n02965783\\",
    //    "n02974003\\",
    //    "n02977058\\",
    //    "n03014705\\",
    //    "n03085013\\",
    //    "n03218198\\",
    //    "n03255030\\",
    //    "n03325584\\",
    //    "n03388043\\",
    //    "n03443371\\",
    //    "n03590841\\",
    //    "n03594734\\",
    //    "n03642806\\",
    //    "n03710193\\",
    //    "n03724870\\",
    //    "n03770439\\",
    //    "n03775071\\",
    //    "n03788195\\",
    //    "n03793489\\",
    //    "n03814906\\",
    //    "n03825788\\",
    //    "n03832673\\",
    //    "n03857828\\",
    //    "n03877845\\",
    //    "n03938244\\",
    //    "n03982430\\",
    //    "n04008634\\",
    //    "n04033995\\",
    //    "n04069434\\",
    //    "n04074963\\",
    //    "n04081281\\",
    //    "n04090263\\",
    //    "n04120489\\",
    //    "n04273569\\",
    //    "n04350905\\",
    //    "n04389033\\",
    //    "n04399382\\",
    //    "n04447861\\",
    //    "n04456115\\",
    //    "n04465501\\",
    //    "n04507155\\",
    //    "n06794110\\",
    //    "n06874185\\",
    //    "n07615774\\",
    //    "n07714990\\",
    //    "n07715103\\",
    //    "n07718472\\",
    //    "n07753275\\",
    //    "n07753592\\",
    //    "n07768694\\",
    //    "n11879895\\",
    //    "n11939491\\",
    //    "n12998815\\",
    //    "n15075141\\",                      
    //}; 

    string inDirName[NUM] = 
    {
        "n01667778\\",
        "n01695060\\",
        "n01770393\\",
        "n01784675\\",
        "n01944390\\",
        "n01984695\\",
        "n02056570\\",
        "n02108551\\",
        "n02134084\\",
        "n02236044\\",
        "n02317335\\",
        "n02342885\\",
        "n02395406\\",
        "n02669723\\",
        "n02687172\\",
        "n02692877\\",
        "n02730930\\",
        "n02769748\\",
        "n02790996\\",
        "n02802426\\",
        "n02808440\\",
        "n02837789\\",
        "n02883205\\",
        "n02892767\\",
        "n02906734\\",
        "n02948072\\",
        "n02965783\\",
        "n02974003\\",
        "n02977058\\",
        "n03014705\\",                      
    }; 
    

    for(int j=0; j<NUM; j++)
    {
        vector<string> filelist;
        finddir((inDirPrefix+inDirName[j]).c_str(), filelist, 0, 0);

        for(int i=0; i<filelist.size(); i++)
        {
            //cout << filelist[i] << endl;
            TiXmlDocument *pDoc = NULL;
            string _in = inDirPrefix+inDirName[j]+filelist[i];
            string _out= outDir+filelist[i];
            string strText;

            LoadXML(_in, pDoc);
            if( false == QueryNode_Text(_in, "segmented", strText) ) 
            {
                cout << filelist[i] << endl;
                continue;
            }
            QueryNode_Text(_in, "filename", strText);
            SaveTxtFile(strText, i, filelist.size());
            ModifyNode_Text(pDoc,"folder","VOC2007");
            ModifyNode_Text(pDoc,"filename",strText+".jpg");
            ModifyNode_Text(pDoc,"database","The VOC2007 Database");
            InsertNode_Text(pDoc,"annotation","source","owner","");
            AddNode_Text(pDoc,"source","annotation","PASCAL VOC2007");
            AddNode_Text(pDoc,"source","image","flickr");
            AddNode_Text(pDoc,"source","flickrid","341012865");
            AddNode_Text(pDoc,"owner","flickrid","Fried Camels");
            AddNode_Text(pDoc,"owner","name","Jinky the Fruit Bat");
            SaveXML(_out, pDoc);
        }
    }   
}
#endif


















































































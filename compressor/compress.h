#ifndef COMPRESS_H_INCLUDED
#define COMPRESS_H_INCLUDED

#include"hfmnode.h"

void GetPath();
void SetljwPath();
void SetljwrcdPath();
void CountNum();
void CreateTree();
void getHFMCode(HFMNode* root, std::string HFMCode);
void cmprs();
void Compress();
void DeCompress();
void Init();
void Look();

#endif // COMPRESS_H_INCLUDED

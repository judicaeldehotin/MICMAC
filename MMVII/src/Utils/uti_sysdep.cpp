#include "include/MMVII_all.h"
#include <functional>

namespace MMVII
{
bool NeverHappens() {return false;}


int GlobSysCall(const std::string & aCom, bool SVP) 
{
   int aResult = system(aCom.c_str());
   if (aResult != EXIT_SUCCESS)
   {
      MMVII_INTERNAL_ASSERT_always(SVP,"Syscall for ["+aCom+"]");
   }
   return aResult;
}

std::string removeInternalFormCom(const std::string & aCom)
{
    static std::vector<std::string> internParams={GIP_LevCall, GIP_PGMA, GIP_DirProjGMA};
    std::size_t found;
    std::size_t pos = aCom.size();
    for (auto &aIntParam : internParams)
    {
        found = aCom.find(BLANK + aIntParam + "=");
        if (found<pos) pos=found;
    }
    return aCom.substr(0, pos);
}

int GlobParalSysCallByMkF(const std::string & aNameMkF,const std::list<std::string> & aListCom,int aNbProcess,const std::string & aTaskFilePrefix,bool SVP)
{
   //RemoveFile(const  std::string & aFile,bool SVP)

   cMMVII_Ofs  aOfs(aNameMkF,false);
   int aNumTask=0;
   std::string aStrAllTask = "all : ";

   std::hash<std::string> hasher;

   for (const auto & aNameCom : aListCom)
   {
       //get nameCom without internal params
       std::size_t aComHash = hasher(removeInternalFormCom(aNameCom));
       std::string aNameTask = aTaskFilePrefix + "Task_" + ToStr<std::size_t>(aComHash);
       aStrAllTask += BLANK  + aNameTask;
       aOfs.Ofs() << aNameTask << " :\n";
       aOfs.Ofs() << "\t" << aNameCom <<" && touch " << aNameTask << "\n";
       aNumTask++;
   }
   aOfs.Ofs() << aStrAllTask << "\n";
   aOfs.Ofs() << "\t\n";
   aOfs.Ofs().close();

   std::string aComMake = "make all -f " +  aNameMkF + " -j" + ToStr(aNbProcess);

   return GlobSysCall(aComMake,false);
}




#if   (THE_MACRO_MMVII_SYS==MMVII_SYS_L)
const std::string TheMMVII_SysName = "Gnu/Linux";
int mmvii_NbProcSys()
{
    return sysconf (_SC_NPROCESSORS_CONF);
}
int mmvii_GetPId()
{
    return getpid();
}


#elif (THE_MACRO_MMVII_SYS==MMVII_SYS_W)
const std::string TheMMVII_SysName = "Bill's shit";
int mmvii_NbProcSys()
{
    SYSTEM_INFO sysinfo;
    GetSystemInfo( &sysinfo );
    return sysinfo.dwNumberOfProcessors;
}
int mmvii_GetPId()
{
    return _getpid();
}
#else
const std::string TheMMVII_SysName = "Steve's shit";
int mmvii_GetPId()
{
    MMVII_INTERNAL_ASSERT_always(false,"mmvii_GetPId on "+TheMMVII_SysName);
    return -1;
}
int mmvii_NbProcSys()
{
    MMVII_INTERNAL_ASSERT_always(false,"mmvii_NbProcSys on "+TheMMVII_SysName);
    return -1;
}
#endif

};


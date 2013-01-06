/*Header-MicMac-eLiSe-25/06/2007

MicMac : Multi Image Correspondances par Methodes Automatiques de Correlation
eLiSe  : ELements of an Image Software Environnement

www.micmac.ign.fr


Copyright : Institut Geographique National
Author : Marc Pierrot Deseilligny
Contributors : Gregoire Maillet, Didier Boldo.

[1] M. Pierrot-Deseilligny, N. Paparoditis.
"A multiresolution and optimization-based image matching approach:
An application to surface reconstruction from SPOT5-HRS stereo imagery."
In IAPRS vol XXXVI-1/W41 in ISPRS Workshop On Topographic Mapping From Space
(With Special Emphasis on Small Satellites), Ankara, Turquie, 02-2006.

[2] M. Pierrot-Deseilligny, "MicMac, un lociel de mise en correspondance
d'images, adapte au contexte geograhique" to appears in
Bulletin d'information de l'Institut Geographique National, 2007.

Francais :

MicMac est un logiciel de mise en correspondance d'image adapte
au contexte de recherche en information geographique. Il s'appuie sur
la bibliotheque de manipulation d'image eLiSe. Il est distibue sous la
licences Cecill-B.  Voir en bas de fichier et  http://www.cecill.info.


English :

MicMac is an open source software specialized in image matching
for research in geographic information. MicMac is built on the
eLiSe image library. MicMac is governed by the  "Cecill-B licence".
See below and http://www.cecill.info.

Header-MicMac-eLiSe-25/06/2007*/



#include "StdAfx.h"

#if (ELISE_windows)
#include "direct.h"
#endif



static int NbFopen=0;
#define FullVerifFClose false
static std::map<FILE *,std::string> FCMap2Name;
static std::map<std::string,int>   FCMapCpt;
extern "C" {


	FILE *ElFopen(const char *path, const char *mode)
	{
		NbFopen++;
		FILE * aFRes =  fopen(path,mode);
		if (FullVerifFClose)
		{
			FCMap2Name[aFRes] = path;
			FCMapCpt[path]++;
		}
		return aFRes;
	}


	int ElFclose(FILE *fp)
	{
		NbFopen--;
		if (FullVerifFClose)
		{
			std::string aName = FCMap2Name[fp] ;
			FCMapCpt[aName] --;
			FCMap2Name[fp] = "";
		}

		return fclose(fp);
	}

	void ShowFClose()
	{
		std::cout << "DELTA FCLOSE = " << NbFopen  << " " << FullVerifFClose << " " << FCMapCpt.size()<< "\n";
		if (FullVerifFClose)
		{
			for
				(
				std::map<std::string,int>::const_iterator it=FCMapCpt.begin();
			it!=FCMapCpt.end();
			it++
				)
			{
				if (it->second !=0) // (it->second != "")
				{
					std::cout << "FCLOSED[" << it->first << "]=" <<  it->second  << "\n";
				}
			}
		}
	}

};



// const  std::string  TheFileMMDIR="/usr/local/bin/MicMacConfig.xml";
const  std::string  TheFileMMDIR= TheMicMacInstallDir "MicMacConfig.xml";

FILE  * FopenNN
	(
	const std::string & aName,
	const std::string & aMode,
	const std::string & aMes
	)
{
	FILE * aFP = ElFopen(aName.c_str(),aMode.c_str());
	if (aFP==0)
	{
		std::cout << "For file " << aName << "  mode " << aMode << "\n";
		std::cout << "Context " <<aMes << "\n";
		std::cout << " FopenNN\n";

		ELISE_ASSERT(aFP!=0,aMes.c_str());
	}
	return aFP;
}


static const char * FileTxt = "Ceci est un fichier binaire eLiSe en mode Txt @55%#7$//9840";

INT aEliseCptFileOpen =0;
INT aEliseCptFileOpenMax =0;
INT aEliseCptFileCall =0;

static void DebugFileOpen(INT delta,const std::string & aName)
{

	aEliseCptFileCall++;
	aEliseCptFileOpen += delta;

	if (aEliseCptFileOpen > aEliseCptFileOpenMax)
	{

		aEliseCptFileOpenMax = aEliseCptFileOpen;
		if (0)
		{
			std::cout << "Max Number Of File Opened = " << aEliseCptFileOpenMax
				<< " " << aName
				<< "-----------------------------------------------------\n";
			if (aEliseCptFileOpen==1000)
			{
				std::cout << "Trop de fichiers ouverts ?? \n";
				getchar();
			}
		}
	}
	// cout << "-- Number Of File Opened = " << aEliseCptFileOpen << "\n";
}



#ifndef S_ISREG
int S_ISREG(int v) { return v&_S_IFREG;}
#endif

#ifndef S_ISDIR
int S_ISDIR(int v)
{
	return v&_S_IFDIR;
}
#endif


bool ELISE_fp::MkDirSvp(const std::string & aName )
{
#if (ELISE_unix || ELISE_Cygwin)
	long long int res = mkdir(aName.c_str(),0X7FFFFFFF);
#endif

#if (ELISE_MacOs)
	long long int res = mkdir(aName.c_str(),0XFFFF);
#endif

#if (ELISE_windows)
	int res = _mkdir(aName.c_str());
#endif

	if (res == 0)
		return true;

	struct stat status;
	std::string ms = aName;

#if (ELISE_windows)
	if ((*aName.rbegin() == '/') || (*aName.rbegin() == '\\'))
		ms.resize(ms.size()-1);
#endif

	res = ::stat(ms.c_str(),&status);
	bool result = ((res == 0) && (S_ISDIR(status.st_mode)));
	return result;
}

void  OkStat(const std::string & aFile,struct stat & status)
{
	int aRes = ::stat(aFile.c_str(),&status);

	if (aRes!=0)
	{
		std::cout << "FOR FILE " << aFile << "\n";
		ELISE_ASSERT (false,"Cannot get stat on file");
	}
}

#if (ELISE_windows)
bool DateStrictePlusRecente(const time_t & aT1,const time_t & aT2)
{
	return aT1 > aT2 ;
}
#else
bool DateStrictePlusRecente(const timespec & aT1,const timespec & aT2)
{
	if (aT1.tv_sec> aT2.tv_sec) return true;
	if (aT1.tv_sec< aT2.tv_sec) return false;

	return aT1.tv_nsec > aT2.tv_nsec ;
}
#endif

bool FileStrictPlusRecent(const std::string & aF1,const std::string & aF2)
{
	/*
	std::cout << "GGGGGGGG " << aF1 << " " << ELISE_fp::exist_file(aF1) 
	<< " @@@@@@ " << aF2 << " " << ELISE_fp::exist_file(aF2) << "\n";
	*/
	if (!ELISE_fp::exist_file(aF1)) return false;
	if (!ELISE_fp::exist_file(aF2)) return true;
	struct stat status1;   OkStat(aF1,status1);
	struct stat status2;  OkStat(aF2,status2);

	// std::cout << aF1 << " " << status1.st_mtim.tv_sec << "\n";
	// std::cout << aF2 << " " << status2.st_mtim.tv_sec << "\n";
#if ( ELISE_MacOs)
	return DateStrictePlusRecente(status1.st_mtimespec,status2.st_mtimespec);
#elif (ELISE_windows)
	return DateStrictePlusRecente(status1.st_mtime,status2.st_mtime);
#else
	return DateStrictePlusRecente(status1.st_mtim,status2.st_mtim);
#endif
}

void ELISE_fp::MkDir(const std::string & aName )
{
	if (! MkDirSvp(aName))
	{
		cout << "Dir Name= ["<< aName<<"]\n";
		ELISE_ASSERT(false,"Cannot MkDir");
	}
}


bool ELISE_fp::IsDirectory(const std::string &  aName )
{
	struct stat status;
	return     (stat(aName.c_str(),&status)== 0)
		&& (S_ISDIR(status.st_mode));
}
void ELISE_fp::AssertIsDirectory(const std::string &  aName )
{
	if (!IsDirectory(aName))
	{
		std::cout << "\n For Name = " << aName << "\n";
		ELISE_ASSERT(false,"Name is not a valid existing directory\n");
	}
}


void ELISE_fp::RmFile(const std::string & aFile)
{
#if ELISE_windows
	string aFileCopy = aFile;
	replace( aFileCopy.begin(), aFileCopy.end(), '/', '\\' );
	std::string aNameCom = std::string(SYS_RM)+" \""+aFileCopy+"\"";
#else
    // MODIF MPD LES "" ne passent pas
	std::string aNameCom = std::string(SYS_RM)+ " " +aFile;
#endif
	VoidSystem(aNameCom.c_str());

}

void  ELISE_fp::PurgeDir(const std::string & aDir)
{
	std::string aDirC = aDir;
	MakeFileDirCompl(aDirC);
#if ELISE_windows
	replace( aDirC.begin(), aDirC.end(), '/', '\\' );
	std::string aCom = std::string(SYS_RM)+" /Q \""+aDirC+"*\"";
#else
    // MODIF MPD LES "" ne permettent pas
	std::string aCom = std::string(SYS_RM)+ " " + aDirC+"*";
#endif
	VoidSystem(aCom.c_str());
}

void ELISE_fp::InterneMkDirRec(const  std::string  & aName )
{
	ELISE_ASSERT(aName!="","ELISE_fp::InterneMkDirRec");
	struct stat status;
   std::string ms = aName;

// même technique que dans MkDirSvp, a modifier par la suite
#if (ELISE_windows)
	if ((*ms.rbegin() == '/') || (*ms.rbegin() == '\\'))
	ms.resize(ms.size()-1);
#endif

   if(    (stat(ms.c_str(),&status)== 0)
		&& (S_ISDIR(status.st_mode))
		)
	{
		return;
	}

	ms.resize(ms.size()-1);
	InterneMkDirRec(DirOfFile(ms));
	MkDir(aName);
}

void ELISE_fp::MkDirRec(const std::string &  aName )
{
    if ( ( *aName.rbegin()!='/' )&&( *aName.rbegin()!='\\' ) )
	{
		InterneMkDirRec(DirOfFile(aName));
	}
	else
	{
		InterneMkDirRec(aName);
	}

}


bool  ELISE_fp::exist_file(const char * aNameFile)
{
	struct stat status;

	bool res =
		(stat(aNameFile,&status)== 0)
		&& (S_ISREG(status.st_mode));


	return res;
}
bool  ELISE_fp::exist_file(const std::string & aName)
{
	return ELISE_fp::exist_file(aName.c_str());
}

void ELISE_fp::if_not_exist_create_0(const char * name,struct stat * status )
{

	if (
		stat(name,status)
		||  (! S_ISREG(status->st_mode))
		)
	{
		ELISE_fp fp(name,ELISE_fp::WRITE);
		fp.close();
		Tjs_El_User.ElAssert
			(
			(stat(name,status)==0)
			&& (S_ISREG(status->st_mode)),
			EEM0 << "Cannot create file " << name
			);
	}

}

const int ELISE_fp::code_mope_seek[3] = {SEEK_SET,SEEK_CUR,SEEK_END};

U_INT1 ELISE_fp::read_U_INT1()
{
	U_INT1 aChar;
	read(&aChar,sizeof(U_INT1),1);
	return aChar;
}
U_INT2 ELISE_fp::read_U_INT2()
{
	U_INT2 c;
	read(&c,sizeof(U_INT2),1);
	if (!_byte_ordered)
		byte_inv_2(&c);
	return c;
}
INT4  ELISE_fp::read_INT4 ()
{
	INT4  c;
	read(&c,sizeof(INT4 ),1,"%d");
	if (!_byte_ordered)
		byte_inv_4(&c);
	return c;
}

INT2  ELISE_fp::read_INT2 ()
{
	INT2  c;
	read(&c,sizeof(INT2 ),1);
	if (!_byte_ordered)
		byte_inv_2(&c);
	return c;
}






REAL4  ELISE_fp::read_REAL4 ()
{
	REAL4  c;
	read(&c,sizeof(REAL4 ),1);
	if (!_byte_ordered)
		byte_inv_4(&c);
	return c;
}

REAL8  ELISE_fp::read_REAL8 ()
{
	REAL8  c;
	read(&c,sizeof(c),1,"%lf");
	ELISE_ASSERT(_byte_ordered,"ELISE_fp::read_REAL8");

	return c;
}



void  ELISE_fp::write(const std::string & aName)
{
	write_INT4(aName.size());
	write(aName.c_str(),sizeof(char),aName.size());
}

std::string  ELISE_fp::read(std::string *)
{
	std::string aRes;

	int aNb= read((INT4 *)0);
	for (int aK=0 ; aK<aNb ; aK++)
	{
		aRes += fgetc();
	}

	return aRes;
}


void ELISE_fp::write_U_INT1(INT v)
{
	U_INT1 c = v;
	write(&c,sizeof(c),1);
}

void ELISE_fp::write_U_INT2(INT v)
{
	U_INT2 c = v;
	write(&c,sizeof(c),1);
}

void ELISE_fp::write_INT4(INT c)
{
	write(&c,sizeof(c),1);
}

void ELISE_fp::write_REAL8(REAL8 c)
{
	write(&c,sizeof(c),1);
}
void ELISE_fp::write_REAL4(float c)
{
	write(&c,sizeof(c),1);
}





U_INT1 ELISE_fp::lsb_read_U_INT1()
{
	return read_U_INT1();
}
U_INT2 ELISE_fp::lsb_read_U_INT2()
{
	U_INT2 c = read_U_INT2();
	to_lsb_rep_2(&c);
	return c;
}
INT4   ELISE_fp::lsb_read_INT4  ()
{
	INT4 c = read_INT4();
	to_lsb_rep_4(&c);
	return c;
}

U_INT1 ELISE_fp::msb_read_U_INT1()
{
	return read_U_INT1();
}
U_INT2 ELISE_fp::msb_read_U_INT2()
{
	U_INT2 c = read_U_INT2();
	to_msb_rep_2(&c);
	return c;
}
INT4   ELISE_fp::msb_read_INT4  ()
{
	INT4 c = read_INT4();
	to_msb_rep_4(&c);
	return c;
}







void ELISE_fp::lsb_write_U_INT2(INT v)
{
	U_INT2 c = v;
	to_lsb_rep_2(&c);
	write_U_INT2(c);
}


extern void d(const char * n);

ELISE_fp::ELISE_fp(const char * name,mode_open mode,bool  svp,eModeBinTxt ModeBinTxt) :
mNameFile (name)
{
	d(name);
	init(ModeBinTxt);
	open(name,mode,svp);
}


void ELISE_fp::set_byte_ordered(bool byte_ordered)
{
	_byte_ordered = byte_ordered;
}

void ELISE_fp::init(eModeBinTxt aModeBinTxt)
{
	_last_act_read = true ; // why not
	_byte_ordered  = true;
	mModeBinTxt  = aModeBinTxt;
}

void  ELISE_fp::str_write(const char * str)
{
	write(const_cast<char *>(str),strlen(str),1);
}


void  ELISE_fp::write_dummy(size_t nb_byte)
{
	static const INT sz_buf = 500;
	U_INT1   buf_local[sz_buf];


	for
		(
		INT nb = 0;
	nb<(INT)nb_byte ;
	nb += sz_buf
		)
	{
		INT nb_loc = ElMin(sz_buf,(INT)nb_byte-nb);
		if (!nb)
			MEM_RAZ(buf_local,nb_loc);
		write(buf_local,sizeof(U_INT1),nb_loc);
	}
}

#define aTBUF 2000
char * ELISE_fp::std_fgets()
{
	static string aBigBuf(aTBUF,'\0');//static char aBigBuf[aTBUF]; TEST_OVERFLOW
	bool aEOF;

	bool OK = fgets(aBigBuf,aEOF); //bool OK = fgets(aBigBuf,aTBUF-1,aEOF,false); TEST_OVERFLOW
	if (aEOF || (!OK))  return 0;
	for (char * aC=&(aBigBuf[0]); *aC ; aC++) //for (char * aC=aBigBuf; *aC ; aC++) TEST_OVERFLOW
	{
		if (isspace(*aC)) *aC = ' ' ;
	}
	return &(aBigBuf[0]); //return aBigBuf; TEST_OVERFLOW
}
/* TEST_OVERFLOW
bool  ELISE_fp::fgets(char * s,INT sz,bool &endof,bool svp)
{
	for (INT i = 0; ; )
	{
		INT c = fgetc();
		bool ok_end = (c == '\n') || (c== eof);
		if (ok_end || (i == sz-1))
		{
			s[i] = 0;
			if (! svp)
				El_Internal.ElAssert
				(
				ok_end,
				EEM0 << "insufficient buffer in ELISE_fp::fgets"
				);
			endof = (c== eof);
			return ok_end;
		}
		// if (isascii(c) && (c!=13))
		if (c!=13)
		{
			s[i] = c;
			i++;
		}
	}
	El_Internal.ElAssert(0,EEM0 << "should not be here in ELISE_fp::fgets");
	return false;
}
*/
// get the next line in the file
bool  ELISE_fp::fgets( std::string &s, bool & endof )
{
	for (INT i = 0; ; )
	{
		INT c = fgetc();
		if ( i==int(s.length()) ) s.resize( s.length()+500 );
		if ( ( c=='\n' ) || ( c==eof ) )
		{
			s[i] = 0;
			endof = ( c==eof );
			return true;
		}
		// if (isascii(c) && (c!=13))
		if (c!=13)
		{
			s[i] = c;
			i++;
		}
	}
	El_Internal.ElAssert(0,EEM0 << "should not be here in ELISE_fp::fgets");
	return false;
}




//=======================================================
#if BUG_CPP_Fclose    // use close,open, read ....
//=======================================================

#include <sys/types.h>
#include <sys/stat.h>
#include <cfcntl>
#include <cunistd>




const int ELISE_fp::code_mope_open[3] = {O_RDONLY,O_WRONLY,O_RDWR};


ELISE_fp::ELISE_fp(eModeBinTxt ModeBin) :
_fd  (-1)
{
	init(ModeBin);
}



bool   ELISE_fp::open(const char * name,mode_open mode,bool  svp)
{
	ELISE_ASSERT(mModeBinTxt==eBinTjs,"No Mode Txt with LoawLevelFileSystem");
	El_Internal.ElAssert
		(
		(!ELISE_windows),
		EEM0 << "Use Fopen/Fclose on Windows"
		);
	INT code = code_mope_open[(INT)mode];
	if (mode == WRITE)
		code = code | O_CREAT | O_TRUNC;

	_fd = ::open(name,code,S_IRWXU);

	if (! svp)
		Tjs_El_User.ElAssert
		(    _fd >=0 ,
		EEM0 << " can't open file : \n"
		<<  "|     "  <<   name << " in mode "
		<<  code_mope_open[(INT)mode]  << "\n"
		<<  "(fd = " << _fd << ")\n"
		);

	return _fd >= 0;
}

bool  ELISE_fp::closed() const
{
	return _fd != -1;
}

bool  ELISE_fp::close(bool svp)
{
	bool res = true;
	if (_fd != -1)
	{
		res =  ! (::close(_fd));
		_fd = -1;
	}
	if (! svp)
		ASSERT_TJS_USER (res,"Error while file closing");
	return res;
}

bool ELISE_fp::seek(long offset, mode_seek mode,bool svp)
{
	bool res = (lseek(_fd,offset,code_mope_seek[(int) mode])>=0);
	if (! svp)
		ASSERT_TJS_USER(res , "Error while file seeking");
	return res;
}

void ELISE_fp::read(void *ptr, size_t size, size_t nmemb)
{
	if (nmemb)
	{
		set_last_act_read(true);
		char * c = (char *) ptr;
		int  nb = size * nmemb;

		for (int i=0; i<nb ; i+=SSIZE_MAX)
		{
			int nb_loc = ElMin((int)SSIZE_MAX,nb-i);
			ASSERT_TJS_USER
				(
				::read(_fd,c+i,nb_loc) == nb_loc,
				"Error while file reading"
				);
		}
	}
}

INT ELISE_fp::fgetc()
{
	U_INT1 c;

	set_last_act_read(true);
	switch (::read(_fd,&c,1))
	{
	case 1 : return c;
	case 0 : return eof;
	default :
		elise_internal_error
			(
			"incoherence in fgetc",
			__FILE__,__LINE__
			);
		return 0;
	}
}

void ELISE_fp::write(const void *ptr, size_t size, size_t nmemb)
{
	set_last_act_read(false);
	if (nmemb)
	{
		int  nb = size * nmemb;
		ASSERT_TJS_USER
			(
			::write(_fd,ptr,nb) == nb,
			"Error while file writing"
			);
	}
}

unsigned long int ELISE_fp::tell()
{
	return lseek(_fd,0,SEEK_CUR);
}

//===================================================================
#else    // use Fclose,Fopen, fread ....
//===================================================================


const char * (ELISE_fp::name_mope_open[3]) = {"rb","wb","r+b"};

ELISE_fp::ELISE_fp(eModeBinTxt ModeBin) :  // use Fclose,Fopen, fread ....
mNameFile ("NoName???"),
	_fp ((FILE *) 0)
{
	init(ModeBin);
}

bool   ELISE_fp::open(const char * name,mode_open mode,bool  svp)
{
	_fp = ElFopen(name,name_mope_open[(INT)mode]);
	DebugFileOpen(1,name);
	if (_fp == (FILE *) NULL)
	{
		if ( svp)
			return false;
		else
		{
			printf("NAME = [%s]\n",name);

			Tjs_El_User.ElAssert
				(   false,
				EEM0 << " can't open file : \n"
				<<  "|     ["  <<  name << "](in mode "
				<<  name_mope_open[(INT)mode]  <<")"
				);
		}
	}

	if (mModeBinTxt == eBinTjs)
	{
		mIsModeBin = true;
	}
	else if (mModeBinTxt==eTxtTjs)
	{
		mIsModeBin = false;
	}
	else
	{
		ELISE_ASSERT(mode=WRITE," ELISE_fp:: Write Mode for eTxtOnPremierLigne");
		char Buf[100];
		INT aNb = (INT) strlen(FileTxt);
		VoidFgets(Buf,aNb+1,_fp);
		mIsModeBin =  (strcmp(Buf,FileTxt)!=0);
		if (mIsModeBin)
			seek_begin(0);
	}

	return _fp!= (FILE *) NULL;
}

bool  ELISE_fp::closed() const
{
	return _fp != (FILE *) NULL;
}

bool  ELISE_fp::close(bool svp)
{

	bool res = true;
	if (_fp != 0)
	{
		res =  ! (ElFclose(_fp));
		_fp= 0;
		DebugFileOpen(-1,"XXX");
	}
	if (! svp)
		ASSERT_TJS_USER (res,"Error while file closing");
	return res;
}

bool ELISE_fp::seek(long offset, mode_seek mode,bool svp)
{
	bool res = (fseek(_fp,offset,code_mope_seek[(int) mode]) >=0);
	if (! svp)
	{
		if (! res)
		{
			std::cout << " Name= "  << mNameFile << "\n";
			ASSERT_TJS_USER(res , "Error while file seeking");
		}
	}
	return res;
}

void ELISE_fp::read(void *ptr, size_t size, size_t nmemb,const char* format)
{
	set_last_act_read(true);
	if (mIsModeBin)
	{
		if (nmemb)
		{
			size_t nb_read = fread(ptr,size,nmemb,_fp);
			if (nb_read != nmemb)
			{
				Tjs_El_User.ElAssert
					(
					false,
					EEM0 <<  "Error while file reading |\n"
					<<  "    FILE = " <<  mNameFile.c_str() << "  pos = " << (INT) tell()  << "|\n"
					<<  " reading " <<  (INT) nmemb << " , got " << (INT) nb_read << "|"

					);
			}
			ASSERT_TJS_USER(nb_read == nmemb,"Error while file reading");
		}
	}
	else
	{
		ELISE_ASSERT(nmemb==1,"Bad Number ELISE_fp::read\n");
		ELISE_ASSERT(format!=0,"Bad format ELISE_fp::read\n");
		VoidFscanf(_fp,format,ptr);
	}
}

INT  ELISE_fp::fgetc()
{
	set_last_act_read(true);
	return ::fgetc(_fp);
}

void ELISE_fp::write(const void *ptr, size_t size, size_t nmemb)
{
	set_last_act_read(false);
	if (nmemb)
	{
		if (fwrite(ptr,size,nmemb,_fp) != nmemb)
		{
			std::cout << " For file = " << mNameFile << "\n";
			ASSERT_TJS_USER
				(
				false,
				"Error while file reading"
				);
		}
	}
}


unsigned long int ELISE_fp::tell()
{
	return ftell(_fp);
}

#endif

ELISE_fp::~ELISE_fp()
{
	// this->close(true);
}


//=======================================================




/***********************************************************/
/*                                                         */
/*                   Flux_Of_Byte                          */
/*                                                         */
/***********************************************************/


Flux_Of_Byte::~Flux_Of_Byte()
{
}

/***********************************************************/
/*                                                         */
/*                   UnPacked_FOB                          */
/*                                                         */
/***********************************************************/

UnPacked_FOB::UnPacked_FOB(Packed_Flux_Of_Byte * packed,bool to_flush) :
_packed    (packed),
	_to_flush  (to_flush)
{
}

U_INT1 UnPacked_FOB::Getc()
{
	U_INT1 r;

	_packed->Read(&r,1);
	return r;
}

void UnPacked_FOB::Putc(U_INT1 c)
{
	_packed->Write(&c,1);
}

UnPacked_FOB::~UnPacked_FOB()
{
	if (_to_flush)
		delete _packed;
}


INT UnPacked_FOB::tell()
{
	return _packed->tell();
}

/***********************************************************/
/*                                                         */
/*            Packed_Flux_Of_Byte                          */
/*                                                         */
/***********************************************************/

Packed_Flux_Of_Byte::Packed_Flux_Of_Byte(INT sz_el) :
_sz_el (sz_el)
{
}


Packed_Flux_Of_Byte::~Packed_Flux_Of_Byte()
{
}

INT  Packed_Flux_Of_Byte::Rseek(INT nb_el)
{
	static const INT sz_buf = 500;
	U_INT1   buf_local[sz_buf];
	INT  nb_el_buf = sz_buf / _sz_el;

	ASSERT_INTERNAL
		(nb_el_buf != 0,"Insufficient buf in Packed_Flux_Of_Byte::Rseek");

	ASSERT_INTERNAL
		(nb_el>=0,"Rseek-neg in Packed_Flux_Of_Byte");
	for
		(
		INT nb_tot_el = 0;
	nb_tot_el<nb_el ;
	nb_tot_el += nb_el_buf
		)
		Read(buf_local,ElMin(nb_el_buf,nb_el-nb_tot_el));

	return nb_el;
}

void Packed_Flux_Of_Byte::AseekFp(INT)
{
	elise_internal_error
		(
		"AseekFp on illicit Packed_Flux_Of_Byte",
		__FILE__,__LINE__
		);
}

INT Packed_Flux_Of_Byte::Write(const U_INT1 *,INT)
{
	elise_internal_error
		(
		"Write on illicit Packed_Flux_Of_Byte",
		__FILE__,__LINE__
		);
	return 0;
}

/***********************************************************/
/*                                                         */
/*            Std_Packed_Flux_Of_Byte                      */
/*                                                         */
/***********************************************************/

bool Std_Packed_Flux_Of_Byte::compressed() const
{
	return false;
}




Std_Packed_Flux_Of_Byte::Std_Packed_Flux_Of_Byte
	(
	const char * name,
	INT sz_el,
	INT offset_0,
	ELISE_fp::mode_open mode
	) :
Packed_Flux_Of_Byte(sz_el)
{
	_fp.open(name,mode);
	_offset_0 = offset_0;
	_fp.seek(offset_0,ELISE_fp::sbegin);
}


INT Std_Packed_Flux_Of_Byte::Read(U_INT1 * res,INT nb)
{
	_fp.read(res,_sz_el,nb);
	return nb;
}

INT Std_Packed_Flux_Of_Byte::Write(const U_INT1 * res,INT nb)
{
	_fp.write((const void *)res,_sz_el,nb);
	return nb;
}

INT Std_Packed_Flux_Of_Byte::Rseek(INT nb)
{
	_fp.seek(_sz_el*nb,ELISE_fp::scurrent);

	// std::cout  << "f_Byte::Rseek NB= " << nb << "W= " << _fp.tell() << "\n";
	return nb;
}

void  Std_Packed_Flux_Of_Byte::Aseek(INT nb)
{
	_fp.seek(_offset_0+_sz_el*nb,ELISE_fp::sbegin);
}


Std_Packed_Flux_Of_Byte::~Std_Packed_Flux_Of_Byte()
{
	_fp.close();
}

void Std_Packed_Flux_Of_Byte::AseekFp(INT nb)
{
	_fp.seek(nb,ELISE_fp::sbegin);
}

INT Std_Packed_Flux_Of_Byte::tell()
{
	return _fp.tell();
}

ELISE_fp & Std_Packed_Flux_Of_Byte::fp() {return _fp;}


/***********************************************************/
/*                                                         */
/*            Mem_Packed_Flux_Of_Byte                      */
/*                                                         */
/***********************************************************/

Mem_Packed_Flux_Of_Byte::Mem_Packed_Flux_Of_Byte
	(
	INT sz_init,
	INT sz_el
	) :
Packed_Flux_Of_Byte   (sz_el),
	_nb                   (0),
	_sz                   (sz_init),
	_data                 (NEW_VECTEUR(0,sz_init*sz_el,U_INT1))
{
}


bool   Mem_Packed_Flux_Of_Byte::compressed()  const
{
	return false;
}

Mem_Packed_Flux_Of_Byte::~Mem_Packed_Flux_Of_Byte()
{
	DELETE_VECTOR(_data,0);
}


INT Mem_Packed_Flux_Of_Byte::Write(const U_INT1 * vals,INT n)
{
	if (_nb +n > _sz)
	{
		while (_nb+n > _sz)
			_sz *= 2;
		U_INT1 * newd   = NEW_VECTEUR(0,_sz*sz_el(),U_INT1);
		convert(newd,_data,_nb*sz_el());

		DELETE_VECTOR(_data,0);
		_data = newd;
	}

	convert(_data+_nb*sz_el(),vals,n*sz_el());
	_nb += n;
	return n;
}

void  Mem_Packed_Flux_Of_Byte::reset()
{
	_nb = 0;
}


INT Mem_Packed_Flux_Of_Byte::Read(U_INT1 * ,INT)
{
	El_Internal.ElAssert
		(
		0,
		EEM0 << "NO Mem_Packed_Flux_Of_Byte::Read"
		);
	return 0;
}


INT Mem_Packed_Flux_Of_Byte::tell()
{
	El_Internal.ElAssert
		(
		0,
		EEM0 << "NO Mem_Packed_Flux_Of_Byte::Read"
		);
	return 0;
}



const char * ElResParseDir::name () const
{
	return _name;
}
bool  ElResParseDir::is_dir() const
{
	return _is_dir;
}
INT   ElResParseDir::level () const
{
	return _level;
}
const char * ElResParseDir::sub (INT lev) const
{
	return _sub[lev];
}


ElResParseDir::ElResParseDir
	(
	const char * Name,
	bool   Isdir,
	int    Level
	)  :
_name   (Name),
	_is_dir (Isdir),
	_level  (Level)
{
	const char * curs = _name;
	for (INT l =0 ; l < _level ; l++)
	{
		while ((*curs != '/') && (*curs != '\\')) curs++;
		_sub[l] = ++curs;
	}

}

void ElResParseDir::show() const
{

	cout << (_is_dir ? "D" : "F");
	cout << ":" << _level << ":";
	cout << "[" << _name << "]";

	for (int l = 0; l<_level; l++)
		cout <<  " (" << _sub[l] << ")";

	cout << "\n";
}

void RecElParse_dir
	(
	INT    niv ,
	const char * ndir,
	ElActionParseDir & action,
	INT LevelMax
	);



#if (ELISE_unix || ELISE_MacOs || ELISE_Cygwin)
#include <dirent.h>
class cElDirectory
{
public :
	cElDirectory(const std::string& aName) :
	   mDir (opendir(aName.c_str()))
	   {
	   }
	   ~cElDirectory()
	   {
		   if (mDir !=0)
			   closedir(mDir);
	   }

	   bool IsDirectory()
	   {
		   return mDir != 0;
	   }
	   const char * GetNextName()
	   {
		   struct dirent * cont_dir = readdir(mDir);
		   return (cont_dir != 0) ? cont_dir->d_name : 0;
	   }
private :
	DIR  * mDir;
};
#elif (ELISE_windows)
#undef INT
#include "shlobj.h"
class cElDirectory
{
public :
	cElDirectory(const std::string& aName):
			mFirst(true)
	   {
		   if ( ELISE_fp::exist_file(aName) )
				mPattern = aName;
		   else
		   {
			    char lastChar = *aName.rbegin();
				if ( lastChar!='\\' && lastChar!='/' )
					mPattern = aName+"/*";
				else
					mPattern = aName+'*';
		   }
		   mHandleFind = ::FindFirstFile (mPattern.c_str(), &mWFD);
	   }
	   ~cElDirectory()  { ::FindClose(mHandleFind); }

	   bool IsDirectory()
	   {
		   return    (mHandleFind != INVALID_HANDLE_VALUE)
			   && (mWFD.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY);
	   }

	   const char * GetNextName()
	   {
		   if (mFirst)
		   {
			   mFirst=false;
			   return mWFD.cFileName;
		   }
		   if (FindNextFile (mHandleFind, &mWFD))
		   {
			   return mWFD.cFileName;
		   }
		   return 0;

	   }


private :
	std::string        mPattern;
	bool               mFirst;
	HANDLE             mHandleFind;
	WIN32_FIND_DATA	   mWFD;

};
#endif






void RecElParse_dir
	(
	INT    niv ,
	const char * ndir,
	ElActionParseDir & action,
	INT LevelMax
	)
{
	if (niv > LevelMax)
		return;

	cElDirectory aDir(ndir);


	if (! aDir.IsDirectory())
	{
		if(ELISE_fp::exist_file(ndir))
			action.act(ElResParseDir(ndir,false,niv));
		return;
	}

	if (niv < LevelMax)
	{

		action.act(ElResParseDir(ndir,true,niv));

		while(const char * subname = aDir.GetNextName())
		{
			if (subname[0] != '.')
			{
				char * namecompl = NEW_VECTEUR(0,(int) strlen(ndir)+(int) strlen(subname)+10,char);
				if ((ndir[strlen(ndir)-1] != '/') && (ndir[strlen(ndir)-1] != '\\'))
                       sprintf(namecompl,"%s%c%s",ndir,ELISE_CAR_DIR,subname);
				else
					sprintf(namecompl,"%s%s",ndir,subname);

				RecElParse_dir(niv+1,namecompl,action,LevelMax);
				DELETE_VECTOR(namecompl,0);
			}
		}
	}

}

#if (0)

void RecElParse_dir
	(
	INT    niv ,
	const char * ndir,
	ElActionParseDir & action,
	INT LevelMax
	)
{
	if (niv > LevelMax)
		return;

	DIR  * dir = opendir(ndir);

	if (! dir)
	{
		closedir(dir);
		if(ELISE_fp::exist_file(ndir))
			action.act(ElResParseDir(ndir,false,niv));
		return;
	}

	if (niv < LevelMax)
	{

		action.act(ElResParseDir(ndir,true,niv));

		struct dirent * cont_dir;
		while((cont_dir = readdir(dir)))
		{
			char * subname = cont_dir->d_name;
			if (subname[0] != '.')
			{
				char * namecompl = NEW_VECTEUR(0,strlen(ndir)+strlen(subname)+10,char);
				if (ndir[strlen(ndir)-1] != '/')
					sprintf(namecompl,"%s/%s",ndir,subname);
				else
					sprintf(namecompl,"%s%s",ndir,subname);

				RecElParse_dir(niv+1,namecompl,action,LevelMax);
				DELETE_VECTOR(namecompl,0);
			}
		}
	}

	closedir(dir);
}
#endif

void ElParseDir
	(
	const char * ndir,
	ElActionParseDir & action ,
	INT                LevelMax
	)
{
	RecElParse_dir(0,ndir,action,LevelMax);
}



void ELISE_fp::write(const cNupletPtsHomologues & aNupl)
{
	aNupl.write(*this);
}

void ELISE_fp::write(const ElCplePtsHomologues & aCpl)
{
	aCpl.write(*this);
}

void ELISE_fp::write(const REAL4 & aV){ write_REAL4(aV);}
void ELISE_fp::write(const REAL8 & aV){ write_REAL8(aV);}
void ELISE_fp::write(const INT4  & aV){ write_INT4 (aV);}

void ELISE_fp::write(const Pt2dr & aP)
{
	write_REAL8(aP.x);
	write_REAL8(aP.y);
}
void ELISE_fp::write(const Pt2df & aP)
{
	write_REAL4(aP.x);
	write_REAL4(aP.y);
}
void ELISE_fp::write(const Pt2di & aP)
{
	write_INT4(aP.x);
	write_INT4(aP.y);
}



void ELISE_fp::write(const Seg2d & aS)
{
	write(aS.p0());
	write(aS.p1());
}

void ELISE_fp::write(const bool & aBool) { write_INT4(aBool); }
bool ELISE_fp::read(bool *) {return (read_INT4() != 0);}



void ELISE_fp::write(const Pt3dr & aP)
{
	write_REAL8(aP.x);
	write_REAL8(aP.y);
	write_REAL8(aP.z);
}
Pt3dr ELISE_fp::read(Pt3dr * aP)
{
	REAL x = read_REAL8();
	REAL y = read_REAL8();
	REAL z = read_REAL8();

	return Pt3dr(x,y,z);
}


void ELISE_fp::write(const Pt3df & aP)
{
	write_REAL4(aP.x);
	write_REAL4(aP.y);
	write_REAL4(aP.z);
}
Pt3df ELISE_fp::read(Pt3df * aP)
{
	float x = read_REAL4();
	float y = read_REAL4();
	float z = read_REAL4();

	return Pt3df(x,y,z);
}

void ELISE_fp::write(const ElMatrix<REAL> & aMat)
{
	write_INT4(aMat.tx());
	write_INT4(aMat.ty());
	for (INT aY=0 ; aY<aMat.ty() ; aY++)
		for (INT aX=0 ; aX<aMat.tx() ; aX++)
		{
			write_REAL8(aMat(aX,aY));
		}
}

ElMatrix<REAL> ELISE_fp::read(ElMatrix<REAL> *)
{
	INT tX = read_INT4();
	INT tY = read_INT4();
	ElMatrix<REAL> aMat(tX,tY);
	for (INT aY=0 ; aY<aMat.ty() ; aY++)
	{
		for (INT aX=0 ; aX<aMat.tx() ; aX++)
		{
			aMat(aX,aY) = read_REAL8();
		}
	}
	return aMat;
}

void ELISE_fp::write(const ElRotation3D & aRot)
{
	write(aRot.tr());
	write(aRot.Mat());
}

ElRotation3D ELISE_fp::read(ElRotation3D *)
{
	Pt3dr aP = read((Pt3dr *)0);
	ElMatrix<REAL> aMat = read((ElMatrix<REAL> *) 0);

        ELISE_ASSERT(false,"agt::VERIFIER ElRotation3D(aP,aMat,true)\n");
	return ElRotation3D(aP,aMat,true);
}


template <class aType> void write_cont(ELISE_fp & aFile,const aType & aCont)
{
	aFile.write_INT4((int) aCont.size());

	for
		(
		typename aType::const_iterator anIt = aCont.begin();
	anIt != aCont.end();
	anIt++
		)
		aFile.write(*anIt);
}

void ELISE_fp::write(const std::list<Seg2d> & aList)
{
	write_cont(*this,aList);
}

void ELISE_fp::write(const std::list<std::string> & aList)
{
	write_cont(*this,aList);
}

void ELISE_fp::write(const std::vector<REAL> & aV)
{
	write_cont(*this,aV);
}

void ELISE_fp::write(const std::vector<Pt2di> & aV)
{
	write_cont(*this,aV);
}

void ELISE_fp::write(const std::vector<int> & aV)
{
	write_cont(*this,aV);
}


void   ELISE_fp::write(const Polynome2dReal & aPol)
{
	aPol.write(*this);
}
void   ELISE_fp::write(const PolynomialEpipolaireCoordinate & anEpi)
{
	anEpi.write(*this);
}
void   ELISE_fp::write(const CpleEpipolaireCoord & aCple)
{
	aCple.write(*this);
}

void cPackNupletsHom::write(class  ELISE_fp & aFile) const
{
	aFile.write_INT4(mDim);
	write_cont(aFile,mCont);
}



PolynomialEpipolaireCoordinate ELISE_fp::read(PolynomialEpipolaireCoordinate *)
{
	return PolynomialEpipolaireCoordinate::read(*this);
}
CpleEpipolaireCoord * ELISE_fp::read(CpleEpipolaireCoord *)
{
	return CpleEpipolaireCoord::read(*this);
}

Polynome2dReal ELISE_fp::read(Polynome2dReal *)
{
	return Polynome2dReal::read(*this);
}

Pt2dr  ELISE_fp::read(Pt2dr *)
{
	REAL x = read_REAL8();
	REAL y = read_REAL8();

	return Pt2dr(x,y);
}


Pt2df  ELISE_fp::read(Pt2df *)
{
	float x = read_REAL4();
	float y = read_REAL4();

	return Pt2df(x,y);
}


Pt2di  ELISE_fp::read(Pt2di *)
{
	INT x = read_INT4();
	INT y = read_INT4();

	return Pt2di(x,y);

}




Seg2d  ELISE_fp::read(Seg2d *)
{
	Pt2dr p0 = read((Pt2dr *)0);
	Pt2dr p1 = read((Pt2dr *)0);

	return Seg2d(p0,p1);
}

REAL8 ELISE_fp::read(REAL8 *)
{
	return  read_REAL8();
}

INT4 ELISE_fp::read(INT4 *)
{
	return  read_INT4();
}

template <class aType> aType read_cont(ELISE_fp & aFile,aType * )
{
	aType aRes;
	INT aNb = aFile.read_INT4();


	while (aNb >0 )
	{
		aRes.push_back(aFile.read((typename aType::value_type *)0));
		aNb--;
	}
	return aRes;
}

ElCplePtsHomologues ELISE_fp::read(ElCplePtsHomologues *)
{
	return cNupletPtsHomologues::read(*this).ToCple();
}
cNupletPtsHomologues ELISE_fp::read(cNupletPtsHomologues *)
{
	return cNupletPtsHomologues::read(*this);
}




std::list<Seg2d> ELISE_fp::read(std::list<Seg2d> *)
{
	return read_cont(*this,(std::list<Seg2d> *)0);
}

std::vector<REAL8> ELISE_fp::read(std::vector<REAL8> *)
{
	return read_cont(*this,(std::vector<REAL8> *)0);
}
std::vector<int> ELISE_fp::read(std::vector<int> *)
{
	return read_cont(*this,(std::vector<int> *)0);
}

std::vector<Pt2di> ELISE_fp::read(std::vector<Pt2di> *)
{
	return read_cont(*this,(std::vector<Pt2di> *)0);
}


template <class Type> void  WritePtr(ELISE_fp & aFile,INT aNb,const Type * aPtr)
{
	for (INT k=0 ; k< aNb ; k++)
		aFile.write(aPtr[k]);
}


template <class Type> void  ReadPtr(ELISE_fp & aFile,INT aNb,Type * aPtr)
{
	for (INT k=0 ; k< aNb ; k++)
		aPtr[k] = aFile.read((Type *) 0);
}

template void WritePtr(ELISE_fp & aFile,INT aNb,const REAL8 *);
template void ReadPtr(ELISE_fp & aFile,INT aNb,REAL8 *);


cPackNupletsHom cPackNupletsHom::read(ELISE_fp & aFile)
{
	int aDim = aFile.read((int*)0);
	cPackNupletsHom aRes(aDim);
	aRes.mCont  = read_cont(aFile,(std::list<cNupletPtsHomologues> *)0);

	return aRes;
}

ElPackHomologue ElPackHomologue::read(ELISE_fp & aFile)
{
	return cPackNupletsHom::read(aFile).ToPckCple();
}

cElOstream::cElOstream(std::ostream  * anOs) :
mOStr  (anOs)
{
}

void RequireBin
	(
	const std::string & ThisBin,
	const std::string & LautreBin,
	const std::string & LeMake
	)
{
	// Version minimaliste pour l'instant

	std::string aCom =
		std::string(g_externalToolHandler.get( "make" ).callName()+" -j2 ")
		+ std::string(" -f")  + LeMake
		+ std::string(" ") + LautreBin;
	VoidSystem(aCom.c_str());
}


INT sizeofile (const char * nom)
{
	struct stat status;
	stat(nom,&status);

	if (S_ISREG(status.st_mode))
		return(status.st_size);
	return 0;
}



/*Footer-MicMac-eLiSe-25/06/2007

Ce logiciel est un programme informatique servant à la mise en
correspondances d'images pour la reconstruction du relief.

Ce logiciel est régi par la licence CeCILL-B soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL-B telle que diffusée par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".

En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme,  le
titulaire des droits patrimoniaux et les concédants successifs.

A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies.  Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation  du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.

Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL-B, et que vous en avez accepté les
termes.
Footer-MicMac-eLiSe-25/06/2007*/

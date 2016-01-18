#include "StdAfx.h"

typedef struct{
	string name;
	int (*func)( int argc, char **argv );
} command_t;

int command_correctPlanarPolygons( int argc, char **argv );
int command_maskContent( int argc, char **argv );
int command_renameImageSet( int argc, char **argv );
int command_toto( int argc, char **argv );
int command_makeSets( int argc, char **argv );

command_t commands[] = {
	{ "correctplanarpolygons", &command_correctPlanarPolygons },
	{ "maskcontent", &command_maskContent },
	{ "renameimageset", &command_renameImageSet },
	{ "toto", &command_toto },
	{ "makesets", &command_makeSets },
	{ "", NULL }
};

void correctPlanarPolygon( vector<Pt3dr> &aPolygon )
{
	if (aPolygon.size() < 3) ELISE_ERROR_EXIT("aPolygon.size() = " << aPolygon.size() << " < 3");
	Pt3dr u = vunit(aPolygon[1] - aPolygon[0]), minV = vunit(aPolygon[2] - aPolygon[0]);
	size_t minI = 2;
	REAL minScal = ElAbs(scal(u, minV));
	for (size_t i = 3; i < aPolygon.size(); i++)
	{
		Pt3dr v = vunit(aPolygon[i] - aPolygon[0]);
		REAL d = ElAbs(scal(u, v));
		if (d < minScal)
		{
			minScal = d;
			minI = i;
			minV = v;
		}
	}
	cout << "minI = " << minI << endl;
	cout << "minScal = " << minScal << endl;
	cout << "minV = " << minV << endl;
	Pt3dr n = u ^ minV;
	cout << "minV = " << minV << endl;
	ElMatrix<REAL> planToGlobalMatrix = MatFromCol(u, minV, n);
	if (planToGlobalMatrix.Det() < 1e-10) ELISE_ERROR_EXIT("matrix is not inversible");

	ElRotation3D planToGlobalRot(aPolygon[0], planToGlobalMatrix, true);
	ElRotation3D globalToPlanRot = planToGlobalRot.inv();

	//~ const size_t nbVertices = aPolygon.size();
	//~ ostringstream ss;
	//~ static int ii = 0;
	//~ const REAL extrudSize = 1e4;
	//~ ss << "polygon_" << (ii++) << ".ply";
	//~ ofstream f(ss.str().c_str());
	//~ f << "ply" << endl;
	//~ f << "format ascii 1.0" << endl;
	//~ f << "element vertex " << 4 * nbVertices << endl;
	//~ f << "property float x" << endl;
	//~ f << "property float y" << endl;
	//~ f << "property float z" << endl;
	//~ f << "property uchar red" << endl;
	//~ f << "property uchar green" << endl;
	//~ f << "property uchar blue" << endl;
	//~ f << "element face " << nbVertices << endl;
	//~ f << "property list uchar int vertex_indices" << endl;
	//~ f << "end_header" << endl;

	REAL zDiffSum = 0.;
	for (size_t i = 0; i < aPolygon.size(); i++)
	{
		Pt3dr p = globalToPlanRot.ImAff(aPolygon[i]);
		zDiffSum += ElAbs(p.z);
		aPolygon[i] = planToGlobalRot.ImAff(Pt3dr(p.x, p.y, 0.));

		//~ Pt3dr p0 = (i == 0) ? aPolygon[aPolygon.size() - 1] : aPolygon[i - 1], p1 = aPolygon[i], p2 = p1 + n * extrudSize, p3 = p0 + n * extrudSize;
		//~ f << p0.x << ' ' << p0.y << ' ' << p0.z << " 128 128 128" << endl;
		//~ f << p1.x << ' ' << p1.y << ' ' << p1.z << " 128 128 128" << endl;
		//~ f << p2.x << ' ' << p2.y << ' ' << p2.z << " 128 128 128" << endl;
		//~ f << p3.x << ' ' << p3.y << ' ' << p3.z << " 128 128 128" << endl;
	}

	//~ for (size_t i = 0; i < aPolygon.size(); i++)
		//~ f << 4 << ' ' << i * 4 << ' ' << i * 4 + 1 << ' ' << i * 4 + 2 << ' ' << i* 4 + 3 << endl;
	//~ f.close();
	cout << "zDiffSum = " << zDiffSum << endl;
}

void correctPlanarPolygons( vector<cItem> &aPolygons )
{
	for (size_t i = 0; i < aPolygons.size(); i++)
		correctPlanarPolygon(aPolygons[i].Pt());
}

void writePolygons( const cPolyg3D &aPolygons, const string &aFilename )
{
	cElXMLFileIn xmlFile(aFilename);
	cElXMLTree *xmlTree = ToXMLTree(aPolygons);
	xmlFile.PutTree(xmlTree);
	delete xmlTree;
}

//~ #if ELISE_QT_VERSION >=4
//~ #include "../saisieQT/include_QT/Cloud.h"
//~ #endif

int command_correctPlanarPolygons( int argc, char **argv )
{
	if (argc < 1) ELISE_ERROR_EXIT("an XML filename is needed");

	const string xmlFilename = argv[0];
	cPolyg3D polygons = StdGetFromSI(xmlFilename, Polyg3D);
	correctPlanarPolygons(polygons.Item());
	writePolygons(polygons, "corrected_polygons.xml");

	return EXIT_SUCCESS;
}


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#if ELISE_QT_VERSION >=4
//~ #if 0
	#include "../saisieQT/include_QT/Cloud.h"
#endif

void getPlyBoundingBox( const string &aFilename, Pt3dr &oP0, Pt3dr &oP1 )
{
	#if ELISE_QT_VERSION >=4
	//~ #if 0
		GlCloud *ply = GlCloud::loadPly(aFilename);
		if ( !ply) ELISE_ERROR_EXIT("cannot load ply file [" << aFilename << ']');

		if (ply->size() == 0) return;

		float min[3], max[3];
		{
			QVector3D p = ply->getVertex(0).getPosition();
			min[0] = max[0] = p.x();
			min[1] = max[1] = p.y();
			min[2] = max[2] = p.z();
		}
		const int plySize = ply->size();
		for (int i = 1; i < plySize; i++)
		{
			QVector3D p = ply->getVertex(i).getPosition();

			if (p.x() < min[0]) min[0] = p.x();
			if (p.y() < min[1]) min[1] = p.y();
			if (p.z() < min[2]) min[2] = p.z();

			if (p.x() > max[0]) max[0] = p.x();
			if (p.y() > max[1]) max[1] = p.y();
			if (p.z() > max[2]) max[2] = p.z();
		}

		oP0 = Pt3dr((REAL)min[0], (REAL)min[1], (REAL)min[2]);
		oP1 = Pt3dr((REAL)max[0], (REAL)max[1], (REAL)max[2]);
	#else
		ELISE_ERROR_EXIT("getPlyBoundingBox: no Qt");
	#endif
}

void makeGrid( const Pt3dr &aP0, const Pt3dr &aSize, unsigned int aPointsPerAxis, const cMasqBin3D &aMask, list<Pt3dr> &oPoints )
{
	ELISE_DEBUG_ERROR(aSize.x <= 0. || aSize.y <= 0. || aSize.z <= 0., "makeGrid", "invalid box size = " << aSize);

	oPoints.clear();
	if (aPointsPerAxis == 0) return;

	Pt3dr pace = aSize / (REAL)(aPointsPerAxis - 1), p;
	const Pt3dr p1 = aP0 + aSize;
	REAL z = aP0.z;
	while (z <= p1.z)
	{
		REAL y = aP0.y;
		while (y <= p1.y)
		{
			REAL x = aP0.x;
			while (x <= p1.x)
			{
				p.x = x;
				p.y = y;
				p.z = z;
				if (aMask.IsInMasq(p)) oPoints.push_back(p);

				x += pace.x;
			}
			y += pace.y;
		}
		z += pace.z;
	}
}

bool writePly( const list<Pt3dr> &aPoints, const string &aFilename )
{
	ofstream f(aFilename.c_str());

	if ( !f) return false;

	f << "ply" << endl;
	f << "format ascii 1.0" << endl;
	f << "element vertex " << aPoints.size() << endl;
	f << "property float x" << endl;
	f << "property float y" << endl;
	f << "property float z" << endl;
	f << "property uchar red" << endl;
	f << "property uchar green" << endl;
	f << "property uchar blue" << endl;
	f << "element face 0" << endl;
	f << "property list uchar int vertex_indices" << endl;
	f << "end_header" << endl;

	list<Pt3dr>::const_iterator itPoint = aPoints.begin();
	while (itPoint != aPoints.end())
	{
		const Pt3dr &p = *itPoint++;
		f << p.x << ' ' << p.y << ' ' << p.z << " 128 128 128" << endl;
	}

	return true;
}

int command_maskContent( int argc, char ** argv )
{
	if (argc < 1) ELISE_ERROR_EXIT("a *_polyg3d.ply file is needed");

	const string maskFilename = argv[1];
	cMasqBin3D *masqBin3D = cMasqBin3D::FromSaisieMasq3d(maskFilename);

	if (masqBin3D == NULL) ELISE_ERROR_EXIT("cannot load mask 3d file [" << maskFilename << "]");

	Pt3dr bbP0, bbP1;
	if (argc >= 2)
	{
		const string plyFilename = argv[1];
		getPlyBoundingBox(plyFilename, bbP0, bbP1);
		cout << "--- bounding box [" << bbP0 << ", " << bbP1 << ']' << endl;

		list<Pt3dr> inMaskPoints;
		makeGrid(bbP0, bbP1 - bbP0, 1000, *masqBin3D, inMaskPoints);
		cout << "--- " << inMaskPoints.size() << " points in mask" << endl;

		const string outputFilename = "maskContent.ply";
		if ( !writePly(inMaskPoints, outputFilename)) ELISE_ERROR_EXIT("failed to write point cloud in [" << outputFilename << ']');
	}

	delete masqBin3D;

	return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

size_t getNbDigits(size_t i_n, unsigned int i_base = 10)
{
	//~ double l = log((double)i_n) / log(i_base);
	//~ unsigned int i = (unsigned int)l;
	//~ if (l != double(i)) return i + 1;
	//~ return i;

	stringstream ss;
	ss << i_n;
	return ss.str().length();
}

int command_renameImageSet( int argc, char **argv )
{
	if (argc < 2) ELISE_ERROR_EXIT("arg0 is a path + regular expression, arg1 is output prefix");

	cElPathRegex fullPattern(argv[0]);
	cElFilename outputBase(argv[1]);
	cout << "input pattern = [" << fullPattern.str() << "]" << endl;
	cout << "output base = [" << outputBase.str() << "]" << endl;

	list<cElFilename> filenames;
	fullPattern.getFilenames(filenames);

	const size_t nbdigits = getNbDigits((unsigned int)filenames.size(), 10);
	size_t iFilename = 0;
	list<cElFilename>::const_iterator itFilename = filenames.begin();
	while (itFilename != filenames.end())
	{
		const cElFilename src = (*itFilename++);
		const string srcStr = src.str();

		stringstream ss;
		ss << outputBase.str() << setw(nbdigits) << setfill('0') << (iFilename++) << getShortestExtension(srcStr);
		cElFilename dst(ss.str());

		cout << '[' << src.str() << "] -> " << dst.str() << endl;

		if (dst.exists())
			cerr << "[" << dst.str() << "] already exists" << endl;
		else if ( !src.copy(dst))
			cerr << "failed to copy [" << src.str() << "] to [" << dst.str() << "]" << endl;
	}

	return EXIT_SUCCESS;
}


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

void dump(const cFileOriMnt &aFileOriMnt, const string &aPrefix = string(), ostream &aStream = cout)
{
	aStream << aPrefix << "NameFileMnt     = [" << aFileOriMnt.NameFileMnt() << ']' << endl;
	if (aFileOriMnt.NameFileMasque().IsInit()) aStream << aPrefix << "NameFileMasque  = [" << aFileOriMnt.NameFileMasque().Val() << ']' << endl;
	aStream << aPrefix << "NombrePixels    = " << aFileOriMnt.NombrePixels() << endl;
	aStream << aPrefix << "OriginePlani    = " << aFileOriMnt.OriginePlani() << endl;
	aStream << aPrefix << "ResolutionPlani = " << aFileOriMnt.ResolutionPlani() << endl;
	aStream << aPrefix << "OrigineAlti     = " << aFileOriMnt.OrigineAlti() << endl;
	aStream << aPrefix << "ResolutionAlti  = " << aFileOriMnt.ResolutionAlti() << endl;
	if (aFileOriMnt.NumZoneLambert().IsInit()) aStream << aPrefix << "NumZoneLambert  = " << aFileOriMnt.NumZoneLambert().Val() << endl;
	aStream << aPrefix << "Geometrie       = " << eToString(aFileOriMnt.Geometrie()) << endl;
	if (aFileOriMnt.OrigineTgtLoc().IsInit()) aStream << aPrefix << "OrigineTgtLoc  = " << aFileOriMnt.OrigineTgtLoc().Val() << endl;
	if (aFileOriMnt.Rounding().IsInit()) aStream << aPrefix << "Rounding  = " << aFileOriMnt.Rounding().Val() << endl;
}

void dump(const cRepereCartesien &aRepereCartesien, const string &aPrefix = string(), ostream &aStream = cout)
{
	aStream << aPrefix << "ori = " << aRepereCartesien.Ori() << endl;
	aStream << aPrefix << "ox  = " << aRepereCartesien.Ox() << endl;
	aStream << aPrefix << "oy  = " << aRepereCartesien.Oy() << endl;
	aStream << aPrefix << "oz  = " << aRepereCartesien.Oz() << endl;
}

int command_toto( int argc, char **argv )
{
	#if 0
		if (argc != 2) ELISE_ERROR_RETURN("usage: src_directory src_directory");

		ctPath src(argv[0]), dst(argv[1]);
		cout << "src: [" << src.str() << ']' << endl;
		cout << "dst: [" << dst.str() << ']' << endl;
		if (src.copy(dst))
			cout << "copy succeeded" << endl;
		else
			cout << "copy failed" << endl;
	#endif

	#if 0
		const string xml_zmap = "/home/jbelvaux/data/Pierrerue_benjamin/Z_Num8_DeZoom2_STD-MALT.xml";
		cFileOriMnt fileOriMNT_zmap = StdGetFromPCP(xml_zmap, FileOriMnt);
		cout << '[' << xml_zmap << ']' << endl;
		dump(fileOriMNT_zmap, "\t");
		cout << endl;

		const string xml_ortho = "/home/jbelvaux/data/Pierrerue_benjamin/MTDOrtho.xml";
		cFileOriMnt fileOriMNT_ortho = StdGetFromPCP(xml_ortho, FileOriMnt);
		cout << '[' << xml_ortho << ']' << endl;
		dump(fileOriMNT_ortho, "\t");
		cout << endl;

		const string xml_repereCartesien = "/home/jbelvaux/data/Pierrerue_benjamin/Repere-Facade1.xml";
		cRepereCartesien repereCartesien = StdGetFromPCP(xml_repereCartesien, RepereCartesien);
		cout << '[' << xml_repereCartesien << ']' << endl;
		dump(repereCartesien, "\t");
		cout << endl;

		const Pt2dr p2d(367.36, 4224.);
		Pt2dr pp2d = ToMnt(fileOriMNT_ortho, p2d);
		cout << "toMNT(" << p2d << ") = " << pp2d << endl << endl;

		const Pt3dr p(367.36, 4224., -1.85795);
		Pt3dr pp = ToMnt(fileOriMNT_ortho, p);
		cout << "toMNT(" << p << ") = " << pp << endl;

		cChCoCart changeCoordCartesiennes = cChCoCart::Xml2El(repereCartesien);
		//~ cout << "f(0., 0., 0.) = " << changeCoordCartesiennes.FromLoc(Pt3dr(0., 0., 0.)) << endl;
		cout << "f(" << pp << ") = " << changeCoordCartesiennes.FromLoc(pp) << endl;
	#endif

	cElRegex pattern(".*Ori-.*/(UnCorMM-|)Orientation.*xml",10);
	if (pattern.Match("Ori-Toto"))
		cout << "yeah !" << endl;
	else
		cout << "oh no !" << endl;

	return EXIT_SUCCESS;
}


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

class ImageSet
{
public:
	class Info
	{
	public:
		string mModel;
		Pt2di mSize;
		double mFocal;

		Info(const cElFilename &aFilename)
		{
			cMetaDataPhoto metaData = cMetaDataPhoto::CreateExiv2(aFilename.str());

			//~ cXmlXifInfo xmlMetaData = MDT2Xml(metaData);
			//~ MakeFileXML(xmlMetaData, StdMetaDataFilename(basename, false)); // false = binary

			mModel = metaData.Cam();
			mSize = metaData.SzImTifOrXif();
			mFocal = metaData.FocMm();
		}

		bool operator !=(const Info &aInfo) const
		{
			return mModel != aInfo.mModel || mSize != aInfo.mSize || mFocal != aInfo.mFocal;
		}
	};

	ImageSet(const Info &aInfo):
		mInfo(aInfo)
	{
	}

	void dump(const string &aPrefix = string(), ostream &aStream = cout) const;

	void move(const string &aBasename) const
	{
		if (mFilenames.empty()) return;

		size_t iFilename = 0;
		size_t nbDigits = getNbDigits(mFilenames.size() - 1);
		list<cElFilename>::const_iterator itFilename = mFilenames.begin();
		while (itFilename != mFilenames.end())
		{
			const string extension = getShortestExtension(itFilename->m_basename);
			ostringstream ss;
			ss << aBasename << '_' << setw(nbDigits) << setfill('0') << iFilename++ << extension;
			const cElFilename newFilename(itFilename->m_path, ss.str());

			cout << "\t[" << itFilename->str() << "] -> [" << newFilename.str() << ']' << endl;
			itFilename->move(newFilename);

			itFilename++;
		}
	}

	Info mInfo;
	list<cElFilename> mFilenames;
};

ostream & operator <<(ostream &aStream, const ImageSet::Info &aInfo)
{
	return (aStream << '[' << aInfo.mModel << "] " << aInfo.mSize.x << 'x' << aInfo.mSize.y << ' ' << aInfo.mFocal);
}

void ImageSet::dump(const string &aPrefix, ostream &aStream) const
{
	aStream << aPrefix << mInfo << endl; 
	list<cElFilename>::const_iterator itFilename = mFilenames.begin();
	while (itFilename != mFilenames.end()) aStream << aPrefix << "\t[" << (*itFilename++).str() << ']' << endl;
}

void add(list<ImageSet> &aSets, const cElFilename &aFilename)
{
	ImageSet::Info info(aFilename);
	list<ImageSet>::iterator it = aSets.begin();
	while (it != aSets.end() && it->mInfo != info) it++;

	if (it == aSets.end())
	{
		aSets.push_back(ImageSet(info));
		it = --aSets.rbegin().base();
	}

	it->mFilenames.push_back(aFilename);
}

void move(list<ImageSet> &aSets, const string &aBase)
{
	if (aSets.empty()) return;

	size_t nbDigits = getNbDigits(aSets.size() - 1);
	size_t iSet = 0;
	list<ImageSet>::iterator it = aSets.begin();
	while (it != aSets.end())
	{
		cout << it->mInfo << ": " << it->mFilenames.size() << " image" << toS(it->mFilenames.size()) << endl;
		ostringstream ss;
		ss << aBase << setw(nbDigits) << setfill('0') << iSet++;
		(*it++).move(ss.str());
	}
}

void dump(const list<ImageSet> &aSets, const string &aPrefix = string(), ostream &aStream = cout)
{
	cout << aSets.size() << " set" << toS(aSets.size()) << endl;
	size_t iSet = 0;
	list<ImageSet>::const_iterator itSet = aSets.begin();
	while (itSet != aSets.end())
	{
		aStream << aPrefix << iSet++ << ": ";
		(*itSet++).dump(aPrefix, aStream);
	}
}

int command_makeSets(int argc, char **argv)
{
	if (argc < 1) ELISE_ERROR_RETURN("missing image filename pattern");

	cElPathRegex fullPattern(argv[0]);

	if ( !fullPattern.m_path.exists()) ELISE_ERROR_RETURN("pattern directory [" << fullPattern.m_path.str() << "] does not existing");

	list<cElFilename> filenames;
	fullPattern.getFilenames(filenames);
	filenames.sort();

	const size_t nbImages = filenames.size();
	if (nbImages == 0) ELISE_ERROR_RETURN("pattern defines no image filename");

	cout << "--- " << nbImages << " image" << toS(nbImages) << endl;

	list<ImageSet> sets;
	list<cElFilename>::const_iterator itFilename = filenames.begin();
	while (itFilename != filenames.end())
		add(sets, *itFilename++);

	const size_t nbSets = sets.size();
	cout << "--- " << nbSets << " set" << toS(nbSets) << endl;

	//~ dump(sets);
	move(sets, "set");

	return EXIT_SUCCESS;
}


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

int TestJB_main( int argc, char **argv )
{
	string command;

	if (argc > 1)
	{
		command = argv[1];
		for (size_t i = 0; i < command.size(); i++)
			command[i] = tolower(command[i]);
	}

	int res = EXIT_FAILURE;
	command_t *itCommand = commands;
	while (itCommand->func != NULL)
	{
		if (itCommand->name == command)
		{
			res = (*itCommand->func)( argc-2, argv+2 );
			break;
		}
		itCommand++;
	}

	if (itCommand->func == NULL)
	{
		cout << "command [" << command << "] is not valid" << endl;
		cout << "commands are :" << endl;
		itCommand = commands;
		while (itCommand->func != NULL)
		{
			cout << '\t' << itCommand->name << endl;
			itCommand++;
		}
	}

	return res;
}

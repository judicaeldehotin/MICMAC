#include "StdAfx.h"

#include <fstream>

using namespace std;

unsigned char DigeoPoint::sm_uchar_descriptor[DIGEO_DESCRIPTOR_SIZE];
REAL8 DigeoPoint::sm_real8_descriptor[DIGEO_DESCRIPTOR_SIZE];
unsigned int DigeoPoint::nbDetectTypes = (int)DigeoPoint::DETECT_UNKNOWN+1; // this is why DETECT_UNKNOWN must stay the last of the enum

/*
class DigeoFileHeader : public VersionedFileHeader
{
public:
	U_INT4 m_nbPoints;
	U_INT4 m_descriptorSize;
	bool   m_reverseByteOrder;

	DigeoFileHeader():VersionedFileHeader(VFH_Digeo){}

	void read( istream &io_stream )
	{
		read_known( VFH_Digeo, io_stream );
		io_stream.read( (char*)&m_nbPoints, 4 );
		io_stream.read( (char*)&m_descriptorSize, 4 );
		m_reverseByteOrder = ( isMSBF()!=MSBF_PROCESSOR() );
		if ( m_reverseByteOrder )
		{
			byte_inv_4( &m_nbPoints );
			byte_inv_4( &m_descriptorSize );
		}
	}
};
*/

void DigeoPoint::addDescriptor( REAL8 i_angle )
{
	entries.resize( entries.size()+1 );
	entries.rbegin()->angle = i_angle;
}

void DigeoPoint::addDescriptor( REAL8 i_angle, const REAL8 *i_descriptor )
{
	addDescriptor( i_angle );
	memcpy( entries.rbegin()->descriptor, i_descriptor, 8*DIGEO_DESCRIPTOR_SIZE );
}

void DigeoPoint::addDescriptor( const REAL8 *i_descriptor )
{
	addDescriptor( i_descriptor[0] );
	memcpy( entries.rbegin()->descriptor, i_descriptor+1, 8*DIGEO_DESCRIPTOR_SIZE );
}

bool DigeoPoint::operator ==( const DigeoPoint &i_b ) const
{
	if ( x!=i_b.x || y!=i_b.y || scale!=i_b.scale || entries.size()!=i_b.entries.size() ) return false;
	for ( size_t i=0; i<entries.size(); i++ ){
		const Entry &descriptorA = entries[i],
		            &descriptorB = i_b.entries[i];
		if ( memcmp( descriptorA.all, descriptorB.all, 8*(DIGEO_DESCRIPTOR_SIZE+1) )!=0 ) return false;
	}
	return true;
}

bool DigeoPoint::operator !=( const DigeoPoint &i_b ) const
{
	return !( *this==i_b );
}

// v0 is the same format as siftpp_tgi (not endian-wise, and no min/max information)
// REAL8 values are cast to float
// descriptor is cast to unsigned char values d[i]->(unsigned char)(512*d[i])
void DigeoPoint::write_v0( ostream &output ) const
{
	REAL4 float_values[4] = { (REAL4)x, (REAL4)y, (REAL4)scale, 0.f };
	const size_t nbAngles = entries.size();
	for ( size_t iAngle=0; iAngle<nbAngles; iAngle++ )
	{
		float_values[3] = (REAL4)entries[iAngle].angle;
		output.write( (char*)float_values, 4*4 );

		// cast descriptor elements to unsigned char before writing
		unsigned char *it_uchar = sm_uchar_descriptor;
		const REAL8 *itReal = entries[iAngle].descriptor;
		size_t i = DIGEO_DESCRIPTOR_SIZE;
		while (i--) (*it_uchar++)=(unsigned char)( 512*(*itReal++) );

		output.write( (char*)sm_uchar_descriptor, DIGEO_DESCRIPTOR_SIZE );
	}
}

void DigeoPoint::write_v1( ostream &output, bool reverseByteOrder ) const
{
	REAL8 real8_values[] = { x, y, scale };
	INT2 int2_values[] = { (INT2)type, (INT2)entries.size() };
	if ( reverseByteOrder )
	{
		byte_inv_8( real8_values );   // x
		byte_inv_8( real8_values+1 ); // y
		byte_inv_8( real8_values+2 ); // scale
		byte_inv_2( int2_values );    // type
		byte_inv_2( int2_values+1 );  // nbAngles
	}
	output.write( (char*)real8_values, 3*8 );
	output.write( (char*)int2_values, 2*2 );

	const size_t nbAngles = entries.size();
	REAL8 angle;
	for ( size_t iAngle=0; iAngle<nbAngles; iAngle++ )
	{
		angle = entries[iAngle].angle;

		// reverse byte order if necessary
		const REAL8 *descriptor_to_write = entries[iAngle].descriptor;
		if ( reverseByteOrder )
		{
			byte_inv_8( &angle );
			memcpy( sm_real8_descriptor, descriptor_to_write, 8*DIGEO_DESCRIPTOR_SIZE );
			REAL8 *it = sm_real8_descriptor;
			unsigned int i = DIGEO_DESCRIPTOR_SIZE;
			while (i--) byte_inv_8( it++ );
			descriptor_to_write = sm_real8_descriptor;
		}

		//write angle
		output.write( (char*)&angle, 8 );
		// write REAL4 descriptor
		output.write( (char*)descriptor_to_write, 8*DIGEO_DESCRIPTOR_SIZE );
	}
}

void DigeoPoint::read_v0( std::istream &output )
{
	REAL4 float_values[4];
	output.read( (char*)float_values, 4*4 );

	x = (REAL8)float_values[0];
	y = (REAL8)float_values[1];
	scale = (REAL8)float_values[2];
	entries.resize(1);
	entries[0].angle = (REAL8)float_values[3]; // angle
	// v0 format do not support different values for this fields
	type = DETECT_UNKNOWN;

	output.read( (char*)sm_uchar_descriptor, DIGEO_DESCRIPTOR_SIZE );

	// cast descriptor elements to REAL4 after reading
	unsigned char *it_uchar = sm_uchar_descriptor;
	REAL8 *itReal = entries[0].descriptor;
	size_t i = DIGEO_DESCRIPTOR_SIZE;
	while (i--) (*itReal++)=( (REAL8)(*it_uchar++)/512 );
}

void DigeoPoint::read_v1( std::istream &output, bool reverseByteOrder )
{
	REAL8 real8_values[3];
	output.read( (char*)real8_values, 3*8 );

	INT2 int2_values[2];
	output.read( (char*)int2_values, 2*2 );

	if ( reverseByteOrder )
	{
		byte_inv_8( real8_values );
		byte_inv_8( real8_values+1 );
		byte_inv_8( real8_values+2 );
		byte_inv_2( int2_values );
		byte_inv_2( int2_values+1 );
	}

	x        = (REAL8)real8_values[0];
	y        = (REAL8)real8_values[1];
	scale    = (REAL8)real8_values[2];
	type     = (DetectType)int2_values[0];
	entries.resize(int2_values[1]);

	// read angle
	const size_t nbAngles = entries.size();
	for ( size_t iAngle=0; iAngle<nbAngles; iAngle++ )
	{
		// read angle and descriptor
		output.read( (char*)entries[iAngle].all, 8*(DIGEO_DESCRIPTOR_SIZE+1) );

		// reverse byte order if necessary
		if ( reverseByteOrder )
		{
			REAL8 *it = entries[iAngle].all;
			int i = DIGEO_DESCRIPTOR_SIZE+1;
			while (i--) byte_inv_8( it++ );
		}
	}
}

//----
// reading functions
//----

void readDigeoFile_v0( istream &stream, bool i_multipleAngles, vector<DigeoPoint> &o_vector )
{   
	// read points
	U_INT4 nbPoints, descriptorSize;
	stream.read( (char*)&nbPoints, 4 );
	stream.read( (char*)&descriptorSize, 4 );

	o_vector.resize(nbPoints);
	DigeoPoint *itPoint = o_vector.data();
	size_t iPoint = o_vector.size();
	while ( iPoint-- ) (*itPoint++).read_v0( stream );

	if ( i_multipleAngles ) DigeoPoint::uniqueToMultipleAngles(o_vector);
}

void readDigeoFile_v1( istream &stream, bool i_reverseByteOrder, bool i_multipleAngles, vector<DigeoPoint> &o_vector )
{
	// read points
	U_INT4 nbPoints, descriptorSize;
	stream.read( (char*)&nbPoints, 4 );
	stream.read( (char*)&descriptorSize, 4 );
	if ( i_reverseByteOrder )
	{
		byte_inv_4( &nbPoints );
		byte_inv_4( &descriptorSize );
	}

	o_vector.resize( nbPoints );
	DigeoPoint *itPoint = o_vector.data();
	size_t iPoint = o_vector.size();
	while ( iPoint-- ) ( *itPoint++ ).read_v1( stream, i_reverseByteOrder );
	if ( !i_multipleAngles ) DigeoPoint::multipleToUniqueAngle(o_vector);
}

// this reading function detects the fileformat and can be used with old siftpp_tgi files
// if o_header is not null, addressed variable is filled
bool DigeoPoint::readDigeoFile( const string &i_filename, bool i_allowMultipleAngles, vector<DigeoPoint> &o_list, VersionedFileHeader *o_header )
{
	ifstream f( i_filename.c_str(), ios::binary );
	if ( !f ) return false;

	VersionedFileHeader header;
	if ( !header.read_known( VFH_Digeo, f ) ) return false;
	if ( o_header!=NULL ) *o_header=header;
	bool reverseByteOrder = ( header.isMSBF()!=MSBF_PROCESSOR() );

	switch ( header.version() ){
	case 0: readDigeoFile_v0( f, i_allowMultipleAngles, o_list ); break;
	case 1: readDigeoFile_v1( f, reverseByteOrder, i_allowMultipleAngles, o_list ); break;
	default: cerr << "ERROR: writeDigeoFile : unkown version number " << header.version() << endl; return false;
	}
	return true;
}


//----
// writing functions
//----

bool DigeoPoint::writeDigeoFile( const std::string &i_filename, const std::vector<DigeoPoint> &i_list )
{
	return writeDigeoFile( i_filename, i_list, g_versioned_headers_list[VFH_Digeo].last_handled_version, MSBF_PROCESSOR() );
}

bool DigeoPoint::writeDigeoFile( const std::string &i_filename, const std::list<DigeoPoint> &i_list )
{
	return writeDigeoFile( i_filename, i_list, g_versioned_headers_list[VFH_Digeo].last_handled_version, MSBF_PROCESSOR() );
}

void writeDigeoFile_v0( std::ostream &stream, const vector<DigeoPoint> &i_list )
{
	// the true number of points in the old format is the number of angles
	size_t nbAngles = 0;
	const DigeoPoint *it = i_list.data();
	size_t i = i_list.size();
	while ( i-- ) nbAngles += ( *it++ ).nbAngles();
	U_INT4 nbPoints = (U_INT4)nbAngles;
	U_INT4 descriptorSize = (U_INT4)DIGEO_DESCRIPTOR_SIZE;

	stream.write( (char*)&nbPoints, 4 );
	stream.write( (char*)&descriptorSize, 4 );

	// write points
	if ( i_list.size()==0 ) return;
	i = i_list.size();
	const DigeoPoint *itPoint = i_list.data();
	while ( i-- ) ( *itPoint++ ).write_v0( stream );
}

void writeDigeoFile_v1( std::ostream &stream, const vector<DigeoPoint> &i_list, bool i_writeBigEndian )
{
	bool reverseByteOrder = ( MSBF_PROCESSOR()!=i_writeBigEndian );

	// same has v0
	U_INT4 nbPoints = (U_INT4)i_list.size(),
	       descriptorSize = (U_INT4)DIGEO_DESCRIPTOR_SIZE;
	if ( reverseByteOrder )
	{
		byte_inv_4( &nbPoints );
		byte_inv_4( &descriptorSize );
	}
	stream.write( (char*)&nbPoints, 4 );
	stream.write( (char*)&descriptorSize, 4 );

	// write points
	if ( i_list.size()==0 ) return;
	const DigeoPoint *itPoint = i_list.data();
	size_t iPoint = i_list.size();
	while ( iPoint-- ) ( *itPoint++ ).write_v1( stream, reverseByteOrder );
}

bool DigeoPoint::writeDigeoFile( const string &i_filename, const vector<DigeoPoint> &i_list, U_INT4 i_version, bool i_writeBigEndian )
{
	ofstream f( i_filename.c_str(), ios::binary );
	if ( !f ) return false;

	if ( i_version>0 )
	{
		VersionedFileHeader header( VFH_Digeo, i_version, i_writeBigEndian );
		header.write(f);
	}

	switch( i_version ){
	case 0: writeDigeoFile_v0( f, i_list ); break;
	case 1: writeDigeoFile_v1( f, i_list, i_writeBigEndian ); break;
	default: cerr << "ERROR: writeDigeoFile : unkown version number " << i_version << endl; return false;
	};

	return true;
}

bool DigeoPoint::writeDigeoFile( const string &i_filename, const list<DigeoPoint> &i_list, U_INT4 i_version, bool i_writeBigEndian )
{
	// copy the list into a vector
	size_t listSize = i_list.size();
	vector<DigeoPoint> v( listSize );
	list<DigeoPoint>::const_iterator itSrc = i_list.begin();
	DigeoPoint *itDst = v.data();
	while ( listSize-- ) *itDst++ = *itSrc++;

	return DigeoPoint::writeDigeoFile( i_filename, v, i_version, i_writeBigEndian );
}

void DigeoPoint::uniqueToMultipleAngles( vector<DigeoPoint> &io_points )
{
	DigeoPoint *itPrevious = io_points.data(),
	           *itCurrent = io_points.data()+1;
	unsigned int nbPoints = io_points.size(),
	             i = nbPoints-1;
	if ( nbPoints==0 ) return;
	while ( i-- ){
		DigeoPoint &previous = itPrevious[0],
		           &current = itCurrent[0];
		if ( current.x==previous.x && current.y==previous.y && current.scale==previous.scale && current.type==previous.type ){
			#ifdef __DEBUG_DIGEO
				ELISE_ASSERT( previous.nbAngles<DIGEO_MAX_NB_ANGLES, (string("readDigeoFile_v0: point has more than ")+ToString(DIGEO_MAX_NB_ANGLES)+" angles").c_str() );
			#endif
			if ( previous.entries.size()<DIGEO_MAX_NB_ANGLES ){
				// previous and current point are different only by their angle, we can aggregate them
				previous.addDescriptor( current.entries[0].all );
				nbPoints--;
			}
		}
		else{
			itPrevious++;
			if ( itCurrent!=itPrevious ) *itPrevious=*itCurrent;
		}
		itCurrent++;
	}
	io_points.resize( nbPoints );
}

void DigeoPoint::multipleToUniqueAngle( vector<DigeoPoint> &io_points )
{
	DigeoPoint *itSrc = io_points.data();
	size_t nbPoints = 0,
	       iPoint = io_points.size();
	while ( iPoint-- ) nbPoints += (*itSrc++).entries.size();

	if ( nbPoints==io_points.size() ) return; // there is no multiple angle

	vector<DigeoPoint> res( nbPoints );
	iPoint = io_points.size();
	itSrc = io_points.data();
	DigeoPoint *itDst = res.data();
	while ( iPoint-- ){
		const size_t nbAngles = itSrc->entries.size();
		for ( size_t iAngle=0; iAngle<nbAngles; iAngle++ ){
			itDst->x = itSrc->x;
			itDst->y = itSrc->y;
			itDst->scale = itSrc->scale;
			itDst->type = itSrc->type;
			itDst->entries.resize(1);
			memcpy( itDst->entries[0].all, itSrc->entries[iAngle].all, 8*(DIGEO_DESCRIPTOR_SIZE+1) );
			itDst++;
		}
		itSrc++;
	}
	io_points.swap(res);
}

void DigeoPoint::removePointsOfType( DetectType i_type, vector<DigeoPoint> &io_points )
{
	// compute the number of points of type i_type, ie the number of points to remove
	size_t nbToRemove = 0;
	size_t iPoint = io_points.size();
	DigeoPoint *itSrc = io_points.data();
	while ( iPoint-- ) if ( (*itSrc++).type==i_type ) nbToRemove++;

	if ( nbToRemove==0 ) return;

	// allocate a new vector and copy the points to be kept into it
	vector<DigeoPoint> res( io_points.size()-nbToRemove );
	DigeoPoint *itDst = res.data();
	itSrc = io_points.data();
	iPoint = io_points.size();
	while ( iPoint-- ){
		if ( itSrc->type!=i_type ) *itDst++ = *itSrc;
		itSrc++;
	}
	io_points.swap( res );
}

// --------------------------------------------------------------
// DigeoPoint related functions
// --------------------------------------------------------------

ostream & operator <<( ostream &s, const DigeoPoint &p )
{
	s << p.x << ',' << p.y << ' ' << p.scale << ' ' << p.nbAngles() << endl;
	for ( size_t i=0; i<p.nbAngles(); i++ ){
		s << '\t' << p.angle(i) << " :";
		const REAL8 *it = p.descriptor(i);
		for ( int j=0; j<DIGEO_DESCRIPTOR_SIZE; j++ )
			s << ' ' << it[j];
		s << endl;
	}
	return s;
}

string DetectType_to_string( DigeoPoint::DetectType i_type )
{
	switch ( i_type ){
	case DigeoPoint::DETECT_LOCAL_MIN: return "DETECT_LOCAL_MIN";
	case DigeoPoint::DETECT_LOCAL_MAX: return "DETECT_LOCAL_MAX";
	case DigeoPoint::DETECT_UNKNOWN: return "DETECT_UNKNOWN";
	}
	return "<invalid>";
}

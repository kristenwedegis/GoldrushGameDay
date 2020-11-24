
//{{BLOCK(poms)

//======================================================================
//
//	poms, 512x256@4, 
//	+ palette 256 entries, not compressed
//	+ 86 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 512 + 2752 + 4096 = 7360
//
//	Time-stamp: 2020-11-08, 14:58:23
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_POMS_H
#define GRIT_POMS_H

#define pomsTilesLen 2752
extern const unsigned short pomsTiles[1376];

#define pomsMapLen 4096
extern const unsigned short pomsMap[2048];

#define pomsPalLen 512
extern const unsigned short pomsPal[256];

#endif // GRIT_POMS_H

//}}BLOCK(poms)

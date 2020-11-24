
//{{BLOCK(level1bg)

//======================================================================
//
//	level1bg, 512x512@4, 
//	+ palette 256 entries, not compressed
//	+ 461 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 512 + 14752 + 8192 = 23456
//
//	Time-stamp: 2020-11-03, 11:03:25
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LEVEL1BG_H
#define GRIT_LEVEL1BG_H

#define level1bgTilesLen 14752
extern const unsigned short level1bgTiles[7376];

#define level1bgMapLen 8192
extern const unsigned short level1bgMap[4096];

#define level1bgPalLen 512
extern const unsigned short level1bgPal[256];

#endif // GRIT_LEVEL1BG_H

//}}BLOCK(level1bg)

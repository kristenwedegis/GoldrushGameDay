
//{{BLOCK(win1)

//======================================================================
//
//	win1, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 547 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 17504 + 2048 = 20064
//
//	Time-stamp: 2020-11-03, 19:59:20
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_WIN1_H
#define GRIT_WIN1_H

#define win1TilesLen 17504
extern const unsigned short win1Tiles[8752];

#define win1MapLen 2048
extern const unsigned short win1Map[1024];

#define win1PalLen 512
extern const unsigned short win1Pal[256];

#endif // GRIT_WIN1_H

//}}BLOCK(win1)

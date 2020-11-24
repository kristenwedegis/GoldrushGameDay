
//{{BLOCK(win2)

//======================================================================
//
//	win2, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 557 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 17824 + 2048 = 20384
//
//	Time-stamp: 2020-11-03, 19:59:39
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_WIN2_H
#define GRIT_WIN2_H

#define win2TilesLen 17824
extern const unsigned short win2Tiles[8912];

#define win2MapLen 2048
extern const unsigned short win2Map[1024];

#define win2PalLen 512
extern const unsigned short win2Pal[256];

#endif // GRIT_WIN2_H

//}}BLOCK(win2)


//{{BLOCK(pause)

//======================================================================
//
//	pause, 512x256@4, 
//	+ palette 256 entries, not compressed
//	+ 672 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 512 + 21504 + 4096 = 26112
//
//	Time-stamp: 2020-11-08, 14:59:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PAUSE_H
#define GRIT_PAUSE_H

#define pauseTilesLen 21504
extern const unsigned short pauseTiles[10752];

#define pauseMapLen 4096
extern const unsigned short pauseMap[2048];

#define pausePalLen 512
extern const unsigned short pausePal[256];

#endif // GRIT_PAUSE_H

//}}BLOCK(pause)


//{{BLOCK(b1)

//======================================================================
//
//	b1, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 318 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 10176 + 2048 = 12736
//
//	Time-stamp: 2018-11-13, 21:37:44
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_B1_H
#define GRIT_B1_H

#define b1TilesLen 10176
extern const unsigned int b1Tiles[2544];

#define b1MapLen 2048
extern const unsigned short b1Map[1024];

#define b1PalLen 512
extern const unsigned short b1Pal[256];

#endif // GRIT_B1_H

//}}BLOCK(b1)

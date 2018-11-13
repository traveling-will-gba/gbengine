
//{{BLOCK(b0)

//======================================================================
//
//	b0, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 277 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 32 + 8864 + 2048 = 10944
//
//	Time-stamp: 2018-11-13, 21:51:34
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_B0_H
#define GRIT_B0_H

#define b0TilesLen 8864
extern const unsigned int b0Tiles[2216];

#define b0MapLen 2048
extern const unsigned short b0Map[1024];

#define b0PalLen 32
extern const unsigned short b0Pal[16];

#endif // GRIT_B0_H

//}}BLOCK(b0)

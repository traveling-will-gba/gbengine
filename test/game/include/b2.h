
//{{BLOCK(b2)

//======================================================================
//
//	b2, 256x160@4, 
//	+ palette 16 entries, not compressed
//	+ 277 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x20 
//	Total size: 32 + 8864 + 1280 = 10176
//
//	Time-stamp: 2018-11-16, 11:47:58
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_B2_H
#define GRIT_B2_H

#define b2TilesLen 8864
extern const unsigned int b2Tiles[2216];

#define b2MapLen 1280
extern const unsigned short b2Map[640];

#define b2PalLen 32
extern const unsigned short b2Pal[16];

#endif // GRIT_B2_H

//}}BLOCK(b2)

xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 45;
 -2.20000;37.81858;-2.20000;,
 2.20000;37.81858;-2.20000;,
 2.20000;33.41858;-2.20000;,
 -2.20000;33.41858;-2.20000;,
 2.20000;37.81858;2.20000;,
 2.20000;33.41858;2.20000;,
 -2.20000;37.81858;2.20000;,
 -2.20000;33.41858;2.20000;,
 -3.27500;32.13758;-2.90240;,
 3.27500;32.13758;-2.90240;,
 3.27500;25.58758;-2.90240;,
 -3.27500;25.58758;-2.90240;,
 3.27500;32.13758;2.80354;,
 3.27500;25.58758;2.80354;,
 -3.27500;32.13758;2.80354;,
 -3.27500;25.58758;2.80354;,
 -3.00000;25.02358;-2.39689;,
 3.00000;25.02358;-2.39689;,
 3.00000;21.89358;-2.39689;,
 -3.00000;21.89358;-2.39689;,
 3.00000;25.02358;2.39689;,
 3.00000;21.89358;2.39689;,
 -3.00000;25.02358;2.39689;,
 -3.00000;21.89358;2.39689;,
 -3.00000;21.55758;-2.39689;,
 3.00000;21.55758;-2.39689;,
 3.00000;18.42758;-2.39689;,
 -3.00000;18.42758;-2.39689;,
 3.00000;21.55758;2.39689;,
 3.00000;18.42758;2.39689;,
 -3.00000;21.55758;2.39689;,
 -3.00000;18.42758;2.39689;,
 -1.34500;33.06958;-0.53800;,
 1.34500;33.06958;-0.53800;,
 1.34500;32.12958;-0.53800;,
 -1.34500;32.12958;-0.53800;,
 1.34500;33.06958;1.78200;,
 1.34500;32.12958;1.78200;,
 -1.34500;33.06958;1.78200;,
 -1.34500;32.12958;1.78200;,
 0.00000;34.58600;-3.02651;,
 0.00000;35.94600;-2.09651;,
 0.80540;34.58600;-1.63151;,
 -0.80540;34.58600;-1.63151;,
 0.00000;34.58600;-2.09651;;
 
 36;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,0,3,7;,
 4;6,4,1,0;,
 4;3,2,5,7;,
 4;8,9,10,11;,
 4;9,12,13,10;,
 4;12,14,15,13;,
 4;14,8,11,15;,
 4;14,12,9,8;,
 4;11,10,13,15;,
 4;16,17,18,19;,
 4;17,20,21,18;,
 4;20,22,23,21;,
 4;22,16,19,23;,
 4;22,20,17,16;,
 4;19,18,21,23;,
 4;24,25,26,27;,
 4;25,28,29,26;,
 4;28,30,31,29;,
 4;30,24,27,31;,
 4;30,28,25,24;,
 4;27,26,29,31;,
 4;32,33,34,35;,
 4;33,36,37,34;,
 4;36,38,39,37;,
 4;38,32,35,39;,
 4;38,36,33,32;,
 4;35,34,37,39;,
 3;40,41,42;,
 3;42,41,43;,
 3;43,41,40;,
 3;44,40,42;,
 3;44,42,43;,
 3;44,43,40;;
 
 MeshMaterialList {
  4;
  36;
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.615200;0.436000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.200000;0.153800;0.109000;;
  }
  Material {
   0.800000;0.040800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.200000;0.010200;0.000000;;
  }
  Material {
   0.006400;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.001600;0.000000;0.200000;;
  }
  Material {
   0.800000;0.772000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.200000;0.193000;0.000000;;
  }
 }
 MeshNormals {
  9;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.819452;0.323523;-0.473109;,
  0.000000;0.323524;0.946220;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.819452;0.323523;-0.473109;;
  36;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;5,5,5,5;,
  3;3,3,3;,
  3;4,4,4;,
  3;8,8,8;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;;
 }
}

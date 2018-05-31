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
 10;
 78.03906;74.40875;-86.90939;,
 78.03907;74.40875;91.66777;,
 78.03907;-0.49645;91.66777;,
 78.03906;-0.49645;-86.90939;,
 -78.03906;74.40875;91.66775;,
 -78.03906;-0.49645;91.66775;,
 -78.03907;74.40875;-86.90941;,
 -78.03907;-0.49645;-86.90941;,
 -78.03907;101.01665;2.26936;,
 78.03907;101.01665;3.74896;;
 
 9;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,0,3,7;,
 4;3,2,5,7;,
 4;8,4,1,9;,
 4;8,9,0,6;,
 3;6,4,8;,
 3;0,9,1;;
 
 MeshMaterialList {
  2;
  9;
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.759200;0.564800;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.520000;0.493480;0.367120;;
  }
  Material {
   0.800000;0.084800;0.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.520000;0.055120;0.000000;;
  }
 }
 MeshNormals {
  12;
  1.000000;-0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  -0.000000;0.000000;1.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.000009;0.999998;0.001931;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.001352;0.957790;0.287467;,
  0.001335;0.958893;-0.283765;,
  -1.000000;-0.000000;0.000000;,
  1.000000;-0.000000;-0.000000;;
  9;
  4;0,0,1,1;,
  4;2,2,2,2;,
  4;3,3,4,4;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;5,8,8,5;,
  4;5,5,9,9;,
  3;3,3,10;,
  3;0,11,0;;
 }
}

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
 72;
 4.49799;1.25794;-2.66682;,
 4.49799;-0.11153;-2.66682;,
 -4.57714;-0.11153;-2.66682;,
 -4.57714;1.25794;-2.66682;,
 -4.57714;3.71691;-2.66682;,
 4.49799;3.71691;-2.66682;,
 4.49799;3.36509;-2.66682;,
 -4.57714;3.36509;-2.66682;,
 4.49799;1.25794;-2.44609;,
 4.49799;3.36509;-2.44609;,
 -4.57714;1.25794;-2.44609;,
 -4.57714;3.36509;-2.44609;,
 -4.57714;6.50480;-2.49256;,
 -4.57714;3.71691;-2.49256;,
 -4.57714;6.50480;-2.66682;,
 4.49799;6.50480;-2.49256;,
 4.49799;6.50480;-2.66682;,
 4.49799;3.71691;-2.49256;,
 -4.57714;6.76870;-2.66682;,
 4.49799;6.76870;-2.66682;,
 -4.57714;9.55931;-2.44609;,
 -4.57714;6.76870;-2.44609;,
 -4.57714;9.55931;-2.66682;,
 4.49799;9.55931;-2.44609;,
 4.49799;9.55931;-2.66682;,
 4.49799;6.76870;-2.44609;,
 4.49799;9.83600;-2.66682;,
 -4.57714;9.83600;-2.66682;,
 4.49799;12.48654;-2.66682;,
 -4.57714;12.48654;-2.66682;,
 -4.57714;13.56878;-2.66682;,
 4.49799;13.56878;-2.66682;,
 4.49799;9.83600;-2.46352;,
 4.49799;12.48654;-2.46352;,
 -4.57714;9.83600;-2.46352;,
 -4.57714;12.48654;-2.46352;,
 4.49799;1.25794;-2.86431;,
 4.49799;3.36509;-2.86431;,
 -4.57714;1.25794;-2.86431;,
 -4.57714;3.36509;-2.86431;,
 -4.57714;6.50480;-2.88174;,
 -4.57714;3.71691;-2.88174;,
 4.49799;6.50480;-2.88174;,
 4.49799;3.71691;-2.88174;,
 -4.57714;9.55931;-2.86431;,
 -4.57714;6.76870;-2.86431;,
 4.49799;9.55931;-2.86431;,
 4.49799;6.76870;-2.86431;,
 4.49799;9.83600;-2.88174;,
 4.49799;12.48654;-2.88174;,
 -4.57714;9.83600;-2.88174;,
 -4.57714;12.48654;-2.88174;,
 -4.73250;-0.11153;-2.66682;,
 -4.73250;-0.11153;2.66682;,
 -4.73250;13.56878;2.66682;,
 -4.73250;13.56878;-2.66682;,
 4.73250;-0.11153;2.66682;,
 4.73250;-0.11153;-2.66682;,
 4.73250;13.56878;-2.66682;,
 4.73250;13.56878;2.66682;,
 -4.73250;-0.11153;-2.66682;,
 -4.73250;13.56878;-2.66682;,
 4.73250;-0.11153;-2.66682;,
 4.73250;13.56878;-2.66682;,
 4.73250;13.56878;-2.66682;,
 -4.73250;13.56878;-2.66682;,
 4.73250;-0.11153;-2.66682;,
 -4.73250;-0.11153;-2.66682;,
 4.73250;-0.11153;2.66682;,
 4.73250;13.56878;2.66682;,
 -4.73250;13.56878;2.66682;,
 -4.73250;-0.11153;2.66682;;
 
 48;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,6,0;,
 4;10,8,0,3;,
 4;11,10,3,7;,
 4;9,11,7,6;,
 4;12,13,4,14;,
 4;15,12,14,16;,
 4;17,15,16,5;,
 4;13,17,5,4;,
 4;18,19,16,14;,
 4;20,21,18,22;,
 4;23,20,22,24;,
 4;25,23,24,19;,
 4;21,25,19,18;,
 4;26,24,22,27;,
 4;28,29,30,31;,
 4;32,33,28,26;,
 4;34,32,26,27;,
 4;35,34,27,29;,
 4;33,35,29,28;,
 4;36,37,9,8;,
 4;38,36,8,10;,
 4;39,38,10,11;,
 4;37,39,11,9;,
 4;37,36,38,39;,
 4;40,41,13,12;,
 4;42,40,12,15;,
 4;43,42,15,17;,
 4;41,43,17,13;,
 4;41,40,42,43;,
 4;44,45,21,20;,
 4;46,44,20,23;,
 4;47,46,23,25;,
 4;45,47,25,21;,
 4;45,44,46,47;,
 4;48,49,33,32;,
 4;50,48,32,34;,
 4;51,50,34,35;,
 4;49,51,35,33;,
 4;49,48,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;2,60,61,30;,
 4;62,1,31,63;,
 4;59,64,65,54;,
 4;66,56,53,67;,
 4;68,69,70,71;;
 
 MeshMaterialList {
  2;
  48;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.674400;0.279200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.329600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  6;
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;;
  48;
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  72;
  0.750000;0.814980;,
  0.750000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.814980;,
  0.500000;0.441620;,
  0.750000;0.441620;,
  0.750000;0.629950;,
  0.500000;0.629950;,
  0.750000;0.814980;,
  0.750000;0.629950;,
  0.500000;0.814980;,
  0.500000;0.629950;,
  0.500000;0.259910;,
  0.500000;0.441620;,
  0.500000;0.259910;,
  0.750000;0.259910;,
  0.750000;0.259910;,
  0.750000;0.441620;,
  0.500000;0.194930;,
  0.750000;0.194930;,
  0.500000;0.129950;,
  0.500000;0.194930;,
  0.500000;0.129950;,
  0.750000;0.129950;,
  0.750000;0.129950;,
  0.750000;0.194930;,
  0.750000;0.064980;,
  0.500000;0.064980;,
  0.750000;0.032490;,
  0.500000;0.032490;,
  0.500000;0.000000;,
  0.750000;0.000000;,
  0.750000;0.064980;,
  0.750000;0.032490;,
  0.500000;0.064980;,
  0.500000;0.032490;,
  0.750000;0.814980;,
  0.750000;0.629950;,
  0.500000;0.814980;,
  0.500000;0.629950;,
  0.500000;0.259910;,
  0.500000;0.441620;,
  0.750000;0.259910;,
  0.750000;0.441620;,
  0.500000;0.129950;,
  0.500000;0.194930;,
  0.750000;0.129950;,
  0.750000;0.194930;,
  0.750000;0.064980;,
  0.750000;0.032490;,
  0.500000;0.064980;,
  0.500000;0.032490;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;;
 }
}

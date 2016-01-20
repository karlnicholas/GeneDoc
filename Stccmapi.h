/*
    GeneDoc: Multiple Sequence Alignment Editing Utility
    Copyright (C) 2000, Karl Nicholas

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifdef _WIN32


char * SCMIEMBL[] = {

"COLORMAP,EMBLESH,\"sheet\",E,255,255,0,0",
"COLORMAP,EMBLESH,\"no pred\", ,255,255,255,0",
"COLORMAP,EMBLESH,\"helix\",H,240,0,128,0",

"COLORMAP,PPPHDHTM,\"Helical Tr.\",H,0,0,255,1",
"COLORMAP,PPPHDHTM,\"No Pred\", ,255,255,255,0",

"COLORMAP,PPSUBHTM,\"Helical Tr.\",H,0,0,255,1",
"COLORMAP,PPSUBHTM,\"No Pred\",.,255,255,255,0",
"COLORMAP,PPSUBHTM,\"Loop\",L,255,0,0,1",

"COLORMAP,EMBL0T9,\"0\",0,0,31,255,1",
"COLORMAP,EMBL0T9,\"1\",1,0,95,255,1",
"COLORMAP,EMBL0T9,\"2\",2,0,191,255,1",
"COLORMAP,EMBL0T9,\"3\",3,0,255,255,1",
"COLORMAP,EMBL0T9,\"4\",4,0,255,95,1",
"COLORMAP,EMBL0T9,\"5\",5,0,255,0,0",
"COLORMAP,EMBL0T9,\"6\",6,127,255,0,0",
"COLORMAP,EMBL0T9,\"7\",7,223,255,0,0",
"COLORMAP,EMBL0T9,\"8\",8,223,159,0,0",
"COLORMAP,EMBL0T9,\"9\",9,255,63,0,1",

"COLORMAP,PPP_3ACC,\"0-9%\",b,0,0,255,1",
"COLORMAP,PPP_3ACC,\"9-36%\", ,255,255,255,0",
"COLORMAP,PPP_3ACC,\"36-100%\",e,255,0,0,1",

"COLORMAP,PPSUBACC,\"0-9%\",b,0,0,255,1",
"COLORMAP,PPSUBACC,\"9-36%\",.,255,255,255,0",
"COLORMAP,PPSUBACC,\"36-100%\",e,255,0,0,1",

"COLORMAP,PPSUBSEC,\"Helix\",H,240,0,128,1",
"COLORMAP,PPSUBSEC,\"Sheet\",E,255,255,0,0",
"COLORMAP,PPSUBSEC,\"no pred\",.,255,255,255,0",
"COLORMAP,PPSUBSEC,\"Loop\",L,96,128,255,1",

"COLORMAP,DSSP,\"Alpha Helix\",H,240,0,128,1",
"COLORMAP,DSSP,\"Beta Bridge Residue\",B,0,255,255,1",
"COLORMAP,DSSP,\"Extended Strand\",E,255,255,0,0",
"COLORMAP,DSSP,\"3/10-Helix\",G,238,130,238,1",
"COLORMAP,DSSP,\"5-Helix\",I,128,0,0,1",
"COLORMAP,DSSP,\"H-bonded Turn\",T,0,0,255,1",
"COLORMAP,DSSP,\"Bend\",S,96,128,255,1",
"COLORMAP,DSSP,\"-\",-,255,255,255,0",

"DATATYPE,\"PHD sec |\",0,0,\"PP PHD SEC\",\"Prot Pred - Structure Prediction\",EMBLESH",
"DATATYPE,\"Rel sec |\",0,0,\"PP REL SEC\",\"Prot Pred - Structure Reliability\",EMBL0T9",
"DATATYPE,\"prH sec |\",0,0,\"PP PRH SEC\",\"Prot Pred - Probability Helix\",EMBL0T9",
"DATATYPE,\"prE sec |\",0,0,\"PP PRE SEC\",\"Prot Pred - Probability Sheet\",EMBL0T9",
"DATATYPE,\"prL sec |\",0,0,\"PP PRL SEC\",\"Prot Pred - Probability Loop\",EMBL0T9",
"DATATYPE,\"SUB sec |\",0,0,\"PP SUB SEC\",\"Prot Pred - Sub Structure\",PPSUBSEC",
"DATATYPE,\"P_3 acc |\",0,0,\"PP P_3 ACC\",\"Prot Pred - Solvent Accessibility in 3 states\",PPP_3ACC",
"DATATYPE,\"PHD acc |\",0,0,\"PP PHD ACC\",\"Prot Pred - Solvent Accessibility\",EMBL0T9",
"DATATYPE,\"Rel acc |\",0,0,\"PP REL ACC\",\"Prot Pred - Solvent Reliability\",EMBL0T9",
"DATATYPE,\"SUB acc |\",0,0,\"PP SUB ACC\",\"Prot Pred - Sub Solvent Accessibility\",PPSUBACC",
"DATATYPE,\"PHD htm |\",0,0,\"PP PHD HTM\", \"Prot Pred - Helical Transmembrane Region\",PPPHDHTM",
"DATATYPE,\"Rel htm |\",0,0,\"PP REL HTM\", \"Prot Pred - Helical Trans. Reliability\",EMBL0T9",
"DATATYPE,\"prH htm |\",0,0,\"PP PRH HTM\", \"Prot Pred - Helical Trans. Probability\",EMBL0T9",
"DATATYPE,\"prL htm |\",0,0,\"PP PRL HTM\", \"Prot Pred - Loop Probability\",EMBL0T9",
"DATATYPE,\"SUB htm |\",0,0,\"PP SUB HTM\", \"Prot Pred - Sub Helical Trans.\",PPSUBHTM",
"DATATYPE,\"Pred SS |\",0,0,\"Pred SS\",\"SS Pred - Prediction\",EMBLESH",
"DATATYPE,\"Clean SS|\",0,0,\"Clean SS\",\"SS Pred - Clean Prediction\",EMBLESH",
"DATATYPE,\"PREDATOR\",0,0,\"Predator\",\"Predator - Prediction\",EMBLESH",
"DATATYPE,\"/2_STR:DSS\",0,0,\"DSSP\",\"Secondary Structure -- DSSP\",DSSP",
};

char * SCMIPDB[] = {

"COLORMAP,PDB,\"Helix\",H,240,0,128,1",
"COLORMAP,PDB,\"Turn\",T,0,0,255,1",
"COLORMAP,PDB,\"Sheet\",S,255,255,0,0",

"DATATYPE,\"PDB\",0,0,\"PDB\",\"Secondary Structure -- PDB\",PDB",
};

char * SCMIPSDB[] = {

"COLORMAP,AMIDE,\"Trans\",T,255,0,0,1",
"COLORMAP,AMIDE,\"Cis\",C,0,255,0,0",
"COLORMAP,AMIDE,\"PseudoTrans\",t,0,0,255,1",
"COLORMAP,AMIDE,\"PseudoCis\",c,255,255,0,0",
"COLORMAP,AMIDE,\"Non Determin.\",-,255,255,255,0",
"COLORMAP,CHIRAL,\"L Isomer\",L,255,0,0,1",
"COLORMAP,CHIRAL,\"D Isomer\",D,0,255,255,1",
"COLORMAP,CHIRAL,\"l Isomer\",l,255,127,0,0",
"COLORMAP,CHIRAL,\"d Isomer\",d,160,32,240,1",
"COLORMAP,CHIRAL,\"Unknown\",?,0,100,0,1",
"COLORMAP,CHIRAL,\"Non Determin.\",X,0,100,0,1",
"COLORMAP,CHIRAL,\"N/A\",-,255,255,255,0",
"COLORMAP,DEERFIELD,\"Type I Turn\",1,255,0,0,1",
"COLORMAP,DEERFIELD,\"Type I' Turn\",!,255,192,203,1",
"COLORMAP,DEERFIELD,\"Type II Turn\",2,176,48,96,1",
"COLORMAP,DEERFIELD,\"Type II' Turn\",@,238,130,238,1",
"COLORMAP,DEERFIELD,\"Type III Turn\",3,208,32,144,1",
"COLORMAP,DEERFIELD,\"Type III' Turn\",#,255,0,255,1",
"COLORMAP,DEERFIELD,\"Type IV Turn\",4,255,0,127,1",
"COLORMAP,DEERFIELD,\"Type V Turn\",5,218,112,214,1",
"COLORMAP,DEERFIELD,\"Type V' Turn\",%,255,127,80,0",
"COLORMAP,DEERFIELD,\"Type VIa Turn\",6,255,99,71,0",
"COLORMAP,DEERFIELD,\"Type VIb Turn\",^,255,218,185,0",
"COLORMAP,DEERFIELD,\"Type VI? Turn\",$,255,228,225,0",
"COLORMAP,DEERFIELD,\"Type VII Turn\",7,255,240,245,0",
"COLORMAP,DEERFIELD,\"Type VIII Turn\",8,255,105,180,1",
"COLORMAP,DEERFIELD,\"Random Coil\",R,0,255,0,0",
"COLORMAP,DEERFIELD,\"Helical\",H,0,0,255,1",
"COLORMAP,DEERFIELD,\"Alpha Helix\",A,0,0,128,1",
"COLORMAP,DEERFIELD,\"Three-Ten Helix\",T,100,149,237,1",
"COLORMAP,DEERFIELD,\"Sheet\",S,255,255,0,0",
"COLORMAP,DEERFIELD,\"Extended\",E,190,190,190,1",
"COLORMAP,DEERFIELD,\"C7Eq\",Q,0,255,255,1",
"COLORMAP,DEERFIELD,\"C7Ax\",X,127,255,212,1",
"COLORMAP,DEERFIELD,\"Left Handed Alpha Helix\",L,135,206,235,1",
"COLORMAP,DEERFIELD,\"Collagen-type Helix\",C,65,105,225,1",
"COLORMAP,DEERFIELD,\"Unknown\",-,0,0,0,1",
"COLORMAP,DEERFIEL4,\"helix\",H,0,0,255,1",
"COLORMAP,DEERFIEL4,\"sheet\",S,255,255,0,0",
"COLORMAP,DEERFIEL4,\"turn\",T,255,0,0,1",
"COLORMAP,DEERFIEL4,\"random\",R,0,255,0,0",
"COLORMAP,DEERFIEL4,\"T1/T3\",h,238,130,238,1",
"COLORMAP,DEERFIEL4,\"-\",-,0,0,0,1",
"COLORMAP,GARNIER,\"Region B\",B,0,0,255,1",
"COLORMAP,GARNIER,\"Region E\",E,0,255,0,0",
"COLORMAP,GARNIER,\"Region F\",F,46,139,87,1",
"COLORMAP,GARNIER,\"Region G\",G,255,255,0,0",
"COLORMAP,GARNIER,\"Region H\",H,255,0,0,1",
"COLORMAP,GARNIER,\"Region I\",I,0,0,128,1",
"COLORMAP,GARNIER,\"Region L\",L,0,255,255,1",
"COLORMAP,GARNIER,\"Region M\",M,255,0,255,1",
"COLORMAP,GARNIER,\"Region N\",N,100,149,237,1",
"COLORMAP,GARNIER,\"Region O\",O,238,130,238,1",
"COLORMAP,GARNIER,\"Region P\",P,255,192,203,1",
"COLORMAP,GARNIER,\"Region S\",S,255,127,0,1",
"COLORMAP,GARNIER,\"Region T\",T,165,42,42,1",
"COLORMAP,GARNIER,\"Region U\",U,190,190,190,1",
"COLORMAP,GARNIER,\"Region *\",*,245,245,220,1",
"COLORMAP,GARNIER,\"Unknown\",-,0,0,0,1",
"COLORMAP,SCHERAGA,\"Region A\",A,255,0,0,1",
"COLORMAP,SCHERAGA,\"Region B\",B,0,255,0,0",
"COLORMAP,SCHERAGA,\"Region C\",C,0,0,255,1",
"COLORMAP,SCHERAGA,\"Region D\",D,255,255,0,1",
"COLORMAP,SCHERAGA,\"Region E\",E,255,127,0,1",
"COLORMAP,SCHERAGA,\"Region F\",F,0,255,255,1",
"COLORMAP,SCHERAGA,\"Region G\",G,255,0,255,1",
"COLORMAP,SCHERAGA,\"Region H\",H,165,42,42,1",
"COLORMAP,SCHERAGA,\"Region A*\",a,190,190,190,1",
"COLORMAP,SCHERAGA,\"Region B*\",b,255,192,203,1",
"COLORMAP,SCHERAGA,\"Region C*\",c,0,0,128,1",
"COLORMAP,SCHERAGA,\"Region D*\",d,238,130,238,1",
"COLORMAP,SCHERAGA,\"Region E*\",e,46,139,87,1",
"COLORMAP,SCHERAGA,\"Region F*\",f,245,245,220,1",
"COLORMAP,SCHERAGA,\"Region G*\",g,100,149,237,1",
"COLORMAP,SCHERAGA,\"Region H*\",h,210,180,140,1",
"COLORMAP,SCHERAGA,\"Unknown\",-,0,0,0,1",
"COLORMAP,SRFGROUP,\"Region E\",E,0,255,0,0",
"COLORMAP,SRFGROUP,\"Region P1\",P,238,130,238,1",
"COLORMAP,SRFGROUP,\"Region P2\",p,0,0,255,1",
"COLORMAP,SRFGROUP,\"Region B1\",B,255,0,0,1",
"COLORMAP,SRFGROUP,\"Region B2\",b,255,255,0,0",
"COLORMAP,SRFGROUP,\"Region B3\",3,255,127,0,0",
"COLORMAP,SRFGROUP,\"Unknown\",?,0,0,0,1",
"COLORMAP,AMH,\"Region A1\",A,255,0,0,1",
"COLORMAP,AMH,\"Region B1\",B,255,44,44,1",
"COLORMAP,AMH,\"Region C1\",C,255,86,86,1",
"COLORMAP,AMH,\"Region D1\",D,255,129,129,1",
"COLORMAP,AMH,\"Region E1\",E,255,171,171,0",
"COLORMAP,AMH,\"Region A2\",a,255,131,0,0",
"COLORMAP,AMH,\"Region B2\",b,255,153,45,0",
"COLORMAP,AMH,\"Region C2\",c,255,173,86,0",
"COLORMAP,AMH,\"Region D2\",d,255,193,128,0",
"COLORMAP,AMH,\"Region E2\",e,255,214,171,0",
"COLORMAP,AMH,\"Region F2\",f,255,234,212,0",
"COLORMAP,AMH,\"Region A3\",1,255,255,0,0",
"COLORMAP,AMH,\"Region B3\",2,255,255,44,0",
"COLORMAP,AMH,\"Region C3\",3,255,255,86,0",
"COLORMAP,AMH,\"Region D3\",4,255,255,129,0",
"COLORMAP,AMH,\"Region E3\",5,245,255,171,0",
"COLORMAP,AMH,\"Region F3\",6,255,255,213,0",
"COLORMAP,AMH,\"Region A4\",!,0,255,0,0",
"COLORMAP,AMH,\"Region B4\",@,44,255,44,1",
"COLORMAP,AMH,\"Region C4\",#,86,255,86,1",
"COLORMAP,AMH,\"Region D4\",$,128,255,128,1",
"COLORMAP,AMH,\"Region E4\",%,171,255,171,1",
"COLORMAP,AMH,\"Region F4\",&,212,252,212,1",
"COLORMAP,AMH,\"Region A5\",[,0,0,255,1",
"COLORMAP,AMH,\"Region B5\",],44,44,255,1",
"COLORMAP,AMH,\"Region C5\",{,86,86,255,1",
"COLORMAP,AMH,\"Region D5\",},128,128,255,1",
"COLORMAP,AMH,\"Region E5\",<,171,171,255,1",
"COLORMAP,AMH,\"Region F5\",>,212,212,255,1",
"COLORMAP,AMH,\"Region A6\",+,131,0,255,1",
"COLORMAP,AMH,\"Region B6\",-,152,44,255,1",
"COLORMAP,AMH,\"Region C6\",*,173,86,255,1",
"COLORMAP,AMH,\"Region D6\",\\,193,128,255,1",
"COLORMAP,AMH,\"Region E6\",^,214,171,255,1",
"COLORMAP,AMH,\"Region F6\",=,234,212,255,1",
"COLORMAP,AMH,\"Region A6\",|,0,0,0,1",
"COLORMAP,AMH,\"Region B6\",?,42,42,42,1",
"COLORMAP,AMH,\"Region C6\",:,84,84,84,1",
"COLORMAP,AMH,\"Region D6\",;,126,126,126,1",
"COLORMAP,AMH,\"Region E6\",\",168,168,168,1",
"COLORMAP,AMH,\"Region F6\",~,210,210,210,1",
"COLORMAP,THORNTON,\"Region B\",B,255,127,0,0",
"COLORMAP,THORNTON,\"Region b\",b,255,171,84,0",
"COLORMAP,THORNTON,\"Region ~b\",6,255,212,169,0",
"COLORMAP,THORNTON,\"Region A\",A,0,0,255,1",
"COLORMAP,THORNTON,\"Region a\",a,84,84,255,1",
"COLORMAP,THORNTON,\"Region ~a\",8,169,169,255,1",
"COLORMAP,THORNTON,\"Region L\",L,0,255,0,0",
"COLORMAP,THORNTON,\"Region l\",l,84,255,84,1",
"COLORMAP,THORNTON,\"Region ~l\",|,169,255,169,1",
"COLORMAP,THORNTON,\"Region p\",P,255,0,255,1",
"COLORMAP,THORNTON,\"Region ~p\",p,255,84,255,1",
"COLORMAP,THORNTON,\"unknown\",X,255,0,0,1",
"COLORMAP,SRFALL,\"0 - 26.13\",0,0,31,255,1",
"COLORMAP,SRFALL,\"26.13 - 52.26\",1,0,95,255,1",
"COLORMAP,SRFALL,\"52.26 - 78.39\",2,0,191,255,1",
"COLORMAP,SRFALL,\"78.39 - 104.52\",3,0,255,255,1",
"COLORMAP,SRFALL,\"104.52 - 130.65\",4,0,255,95,1",
"COLORMAP,SRFALL,\"130.65 - 156.78\",5,0,255,0,0",
"COLORMAP,SRFALL,\"156.78 - 182.91\",6,127,255,0,0",
"COLORMAP,SRFALL,\"182.91 - 209.94\",7,223,255,0,0",
"COLORMAP,SRFALL,\"209.04 - 235.17\",8,223,159,0,0",
"COLORMAP,SRFALL,\"235.17 - 261.3\",9,255,63,0,1",
"COLORMAP,SRFBUR,\"0 - 23.4\",0,0,31,255,1",
"COLORMAP,SRFBUR,\"23.4 - 46.8\",1,0,95,255,1",
"COLORMAP,SRFBUR,\"46.8 - 70.2\",2,0,191,255,1",
"COLORMAP,SRFBUR,\"70.2 - 93.6\",3,0,255,255,1",
"COLORMAP,SRFBUR,\"93.6 - 117.0\",4,0,255,95,1",
"COLORMAP,SRFBUR,\"117.0 - 140.4\",5,0,255,0,0",
"COLORMAP,SRFBUR,\"140.4 - 163.8\",6,127,255,0,0",
"COLORMAP,SRFBUR,\"163.8 - 187.2\",7,223,255,0,0",
"COLORMAP,SRFBUR,\"187.2 - 210.6\",8,223,159,0,0",
"COLORMAP,SRFBUR,\"210.6 - 234.0\",9,255,63,0,1",
"COLORMAP,PERCENT,\"0 - 10\",0,0,31,255,1",
"COLORMAP,PERCENT,\"10 - 20\",1,0,95,255,1",
"COLORMAP,PERCENT,\"20 - 30\",2,0,191,255,1",
"COLORMAP,PERCENT,\"30 - 40\",3,0,255,255,1",
"COLORMAP,PERCENT,\"40 - 50\",4,0,255,95,1",
"COLORMAP,PERCENT,\"50 - 60\",5,0,255,0,0",
"COLORMAP,PERCENT,\"60 - 70\",6,127,255,0,0",
"COLORMAP,PERCENT,\"70 - 80\",7,223,255,0,0",
"COLORMAP,PERCENT,\"80 - 90\",8,223,159,0,0",
"COLORMAP,PERCENT,\"90 - 100\",9,255,63,0,1",
"COLORMAP,RADIAL,\"0 - 1\",a,0,10,255,1",
"COLORMAP,RADIAL,\"1 - 2\",b,0,20,255,1",
"COLORMAP,RADIAL,\"2 - 3\",c,0,30,255,1",
"COLORMAP,RADIAL,\"3 - 4\",d,0,40,255,1",
"COLORMAP,RADIAL,\"4 - 5\",e,0,50,255,1",
"COLORMAP,RADIAL,\"5 - 6\",f,0,61,255,1",
"COLORMAP,RADIAL,\"6 - 7\",g,0,71,255,1",
"COLORMAP,RADIAL,\"7 - 8\",h,0,81,255,1",
"COLORMAP,RADIAL,\"8 - 9\",i,0,91,255,1",
"COLORMAP,RADIAL,\"9 - 10\",j,0,101,255,1",
"COLORMAP,RADIAL,\"10 - 11\",k,0,112,255,1",
"COLORMAP,RADIAL,\"11 - 12\",l,0,122,255,1",
"COLORMAP,RADIAL,\"12 - 13\",m,0,132,255,1",
"COLORMAP,RADIAL,\"13 - 14\",n,0,142,255,1",
"COLORMAP,RADIAL,\"14 - 15\",o,0,152,255,1",
"COLORMAP,RADIAL,\"15 - 16\",p,0,163,255,1",
"COLORMAP,RADIAL,\"16 - 17\",q,0,173,255,1",
"COLORMAP,RADIAL,\"17 - 18\",r,0,183,255,1",
"COLORMAP,RADIAL,\"18 - 19\",s,0,193,255,1",
"COLORMAP,RADIAL,\"19 - 20\",t,0,203,255,1",
"COLORMAP,RADIAL,\"20 - 21\",u,0,214,255,1",
"COLORMAP,RADIAL,\"21 - 22\",v,0,224,255,1",
"COLORMAP,RADIAL,\"22 - 23\",w,0,234,255,1",
"COLORMAP,RADIAL,\"23 - 24\",x,0,244,255,1",
"COLORMAP,RADIAL,\"24 - 25\",y,0,255,255,1",
"COLORMAP,RADIAL,\"25 - 26\",z,0,255,244,1",
"COLORMAP,RADIAL,\"26 - 27\",0,0,255,234,1",
"COLORMAP,RADIAL,\"27 - 28\",1,0,255,224,1",
"COLORMAP,RADIAL,\"28 - 29\",2,0,255,214,1",
"COLORMAP,RADIAL,\"29 - 30\",3,0,255,204,1",
"COLORMAP,RADIAL,\"30 - 31\",4,0,255,193,1",
"COLORMAP,RADIAL,\"31 - 32\",5,0,255,183,1",
"COLORMAP,RADIAL,\"32 - 33\",6,0,255,173,1",
"COLORMAP,RADIAL,\"33 - 34\",7,0,255,163,1",
"COLORMAP,RADIAL,\"34 - 35\",8,0,255,153,1",
"COLORMAP,RADIAL,\"35 - 36\",9,0,255,142,1",
"COLORMAP,RADIAL,\"36 - 37\",A,0,255,132,1",
"COLORMAP,RADIAL,\"37 - 38\",B,0,255,122,1",
"COLORMAP,RADIAL,\"38 - 39\",C,0,255,112,1",
"COLORMAP,RADIAL,\"39 - 40\",D,0,255,101,1",
"COLORMAP,RADIAL,\"40 - 41\",E,0,255,91,1",
"COLORMAP,RADIAL,\"41 - 42\",F,0,255,81,1",
"COLORMAP,RADIAL,\"42 - 43\",G,0,255,71,1",
"COLORMAP,RADIAL,\"43 - 44\",H,0,255,61,1",
"COLORMAP,RADIAL,\"44 - 45\",I,0,255,51,1",
"COLORMAP,RADIAL,\"45 - 46\",J,0,255,40,1",
"COLORMAP,RADIAL,\"46 - 47\",K,0,255,30,1",
"COLORMAP,RADIAL,\"47 - 48\",L,0,255,20,1",
"COLORMAP,RADIAL,\"48 - 49\",M,0,255,10,1",
"COLORMAP,RADIAL,\"49 - 50\",N,0,255,0,0",
"COLORMAP,RADIAL,\"50 - 51\",O,10,255,0,0",
"COLORMAP,RADIAL,\"51 - 52\",P,20,255,0,0",
"COLORMAP,RADIAL,\"52 - 53\",Q,30,255,0,0",
"COLORMAP,RADIAL,\"53 - 54\",R,40,255,0,0",
"COLORMAP,RADIAL,\"54 - 55\",S,50,255,0,0",
"COLORMAP,RADIAL,\"55 - 56\",T,61,255,0,1",
"COLORMAP,RADIAL,\"56 - 57\",U,71,255,0,1",
"COLORMAP,RADIAL,\"57 - 58\",V,81,255,0,1",
"COLORMAP,RADIAL,\"58 - 59\",W,91,255,0,1",
"COLORMAP,RADIAL,\"59 - 60\",X,101,255,0,0",
"COLORMAP,RADIAL,\"60 - 61\",Y,112,255,0,0",
"COLORMAP,RADIAL,\"61 - 62\",Z,122,255,0,0",
"COLORMAP,RADIAL,\"62 - 63\",@,132,255,0,0",
"COLORMAP,RADIAL,\"63 - 64\",#,142,255,0,0",
"COLORMAP,RADIAL,\"64 - 65\",&,152,255,0,0",
"COLORMAP,RADIAL,\"65 - 66\",$,163,255,0,0",
"COLORMAP,RADIAL,\"66 - 67\",!,173,255,0,0",
"COLORMAP,RADIAL,\"67 - 68\",|,183,255,0,0",
"COLORMAP,RADIAL,\"68 - 69\",\\,193,255,0,0",
"COLORMAP,RADIAL,\"69 - 70\",{,203,255,0,0",
"COLORMAP,RADIAL,\"70 - 71\",[,214,255,0,0",
"COLORMAP,RADIAL,\"71 - 72\",(,224,255,0,0",
"COLORMAP,RADIAL,\"72 - 73\",),234,255,0,0",
"COLORMAP,RADIAL,\"73 - 74\",],244,255,0,0",
"COLORMAP,RADIAL,\"74 - 75\",},255,255,0,0",
"COLORMAP,RADIAL,\"75 - 76\",/,255,244,0,0",
"COLORMAP,RADIAL,\"76 - 77\",%,255,234,0,0",
"COLORMAP,RADIAL,\"77 - 78\",^,255,224,0,0",
"COLORMAP,RADIAL,\"78 - 79\",*,255,214,0,0",
"COLORMAP,RADIAL,\"79 - 80\",?,255,204,0,0",
"COLORMAP,RADIAL,\"80 - 81\",=,255,193,0,0",
"COLORMAP,RADIAL,\"81 - 82\",+,255,183,0,0",
"COLORMAP,RADIAL,\"82 - 83\",~,255,173,0,0",
"COLORMAP,RADIAL,\"83 - 84\",-,255,163,0,0",
"COLORMAP,RADIAL,\"84 - 85\",;,255,153,0,0",
"COLORMAP,RADIAL,\"85 - 86\",:,255,142,0,0",
"COLORMAP,RADIAL,\"86 - 87\",,,255,132,0,0",
"COLORMAP,RADIAL,\"87 - 88\",.,255,122,0,1",
"COLORMAP,RADIAL,\"88 - 89\",\",255,112,0,1",
"COLORMAP,RADIAL,\"89 - 90\",`,255,101,0,1",
"COLORMAP,RADIAL,\"90 - 91\",',255,91,0,1",
"COLORMAP,RADIAL,\"91 - 92\",_,255,81,0,1",
"COLORMAP,DSSP,\"Alpha Helix\",H,240,0,128,1",
"COLORMAP,DSSP,\"Beta Bridge Residue\",B,0,255,255,1",
"COLORMAP,DSSP,\"Extended Strand\",E,255,255,0,0",
"COLORMAP,DSSP,\"3/10-Helix\",G,238,130,238,1",
"COLORMAP,DSSP,\"5-Helix\",I,128,0,0,1",
"COLORMAP,DSSP,\"H-bonded Turn\",T,0,0,255,1",
"COLORMAP,DSSP,\"Bend\",S,96,128,255,1",
"COLORMAP,DSSP,\"-\",-,255,255,255,0",

"DATATYPE,\"/CHIRAL:\",0,0,\"Chiral\",\"Chirality\",CHIRAL",
"DATATYPE,\"/AMIDE:\",0,0,\"Amide\",\"Amide\",AMIDE",
"DATATYPE,\"/2_STR:G\",0,0,\"Garnier\",\"Secondary Structure -- Garnier Classification\",GARNIER",
"DATATYPE,\"/2_STR:T\",0,0,\"Thornton\",\"Secondary Structure -- Thornton Classification\",THORNTON",
"DATATYPE,\"/2_STR:S\",0,0,\"Scheraga\",\"Secondary Structure -- Scheraga Classification\",SCHERAGA",
"DATATYPE,\"/2_STR:D\",0,0,\"Deerfield\",\"Secondary Structure -- Deerfield Classification\",DEERFIELD",
"DATATYPE,\"/2_STR:D4\",0,0,\"Deerfield4\",\"Secondary Structure -- Deerfield4 Classification\",DEERFIEL4",
"DATATYPE,\"/2_STR:DSS\",0,0,\"DSSP\",\"Secondary Structure -- DSSP\",DSSP",
"DATATYPE,\"/SRF:ALL\",0,0,\"Srf-All\",\"Surface Area\",SRFALL",
"DATATYPE,\"/SRF:ALL%\",0,0,\"Srf-All%\",\"Surface Area %\",PERCENT",
"DATATYPE,\"/SRF:SID%\",0,0,\"Srf-Side\",\"Sidechain Pct\",PERCENT",
"DATATYPE,\"/SRF:BUR\",0,0,\"Srf-Buried\",\"Buried Area\",SRFBUR",
"DATATYPE,\"/SRF:PFRAC\",0,0,\"Pfrac\",\"PFRAC\",PERCENT",
"DATATYPE,\"/SRF:GROUP\",0,0,\"SrfGroup \",\"Surface Group\",SRFGROUP",
"DATATYPE,\"/SRF:AMH\",0,0,\"AMH \",\"AMH Classification\",AMH",
"DATATYPE,\"/RADIAL:\",0,0,\"Radial\",\"Radial\",RADIAL",
"DATATYPE,\"/SRF:ALL-H\",0,0,\"Srf-All-H\",\"Holomolecule:Surface Area\",SRFALL",
"DATATYPE,\"/SRF:ALL%-H\",0,0,\"Srf-All%-H\",\"Holomolecule:Surface Area %\",PERCENT",
"DATATYPE,\"/SRF:SID%-H\",0,0,\"Srf-Side-H\",\"Holomolecule: Sidechain Pct\",PERCENT",
"DATATYPE,\"/SRF:BUR-H\",0,0,\"Srf-Buried-H\",\"Holomolecule:Buried Area\",SRFBUR",
"DATATYPE,\"/SRF:PFRAC-H\",0,0,\"Pfrac-H\",\"Holomolecule:PFRAC\",PERCENT",
"DATATYPE,\"/SRF:GROUP-H\",0,0,\"SrfGroup-H\",\"Holomolecule:Surface Group\",SRFGROUP",
"DATATYPE,\"/SRF:AMH-H\",0,0,\"AMH-H\",\"Holomolecule:AMH Classification\",AMH", 
"DATATYPE,\"/SRF:ALL-P\",0,0,\"Srf-All-P\",\"Interchain:Surface Area\",SRFALL",
"DATATYPE,\"/SRF:ALL%-P\",0,0,\"Srf-All%-P\",\"Interchain:Surface Area %\",PERCENT",
"DATATYPE,\"/SRF:SID%-P\",0,0,\"Srf-Side-P\",\"Interchain:Sidechain Pct\",PERCENT",
"DATATYPE,\"/SRF:BUR-P\",0,0,\"Srf-Buried-P\",\"Interchain:Buried Area\",SRFBUR",
"DATATYPE,\"/SRF:PFRAC-P\",0,0,\"Prac-P\",\"Interchain:PFRAC\",PERCENT",
"DATATYPE,\"/SRF:GROUP-P\",0,0,\"SrfGroup-P\",\"Interchain:Surface Group\",SRFGROUP",
"DATATYPE,\"/SRF:AMH-P\",0,0,\"AMH-P\",\"Interchain:AMH Classification\",AMH",
"DATATYPE,\"/SRF:ALL-L\",0,0,\"Srf-All-L\",\"Ligands:Surface Area\",SRFALL",
"DATATYPE,\"/SRF:SID%-L\",0,0,\"Srf-All%-L\",\"Ligands:Surface Area %\",PERCENT",
"DATATYPE,\"/SRF:ALL%-L\",0,0,\"Srf-Side-L\",\"Ligands:Sidechain Pct\",PERCENT",
"DATATYPE,\"/SRF:BUR-L\",0,0,\"Srf-Buried-L\",\"Ligands:Buried Area\",SRFBUR",
"DATATYPE,\"/SRF:PFRAC-L\",0,0,\"Prac-L\",\"Ligands:PFRAC\",PERCENT",
"DATATYPE,\"/SRF:GROUP-L\",0,0,\"SrfGroup-L\",\"Ligands:Surface Group\",SRFGROUP",
"DATATYPE,\"/SRF:AMH-L\",0,0,\"AMH-L\",\"Ligands:AMH Classification\",AMH",
"DATATYPE,\"/SRF:ALL-I\",0,0,\"Srf-All-I\",\"Ions:Surface Area\",SRFALL",
"DATATYPE,\"/SRF:ALL%-I\",0,0,\"Srf-All%-I\",\"Ions:Surface Area %\",PERCENT",
"DATATYPE,\"/SRF:SID%-I\",0,0,\"Srf-Side-I\",\"Ions: Sidechain Pct\",PERCENT",
"DATATYPE,\"/SRF:BUR-I\",0,0,\"Srf-Buried-I\",\"Ions:Buried Area\",SRFBUR",
"DATATYPE,\"/SRF:PFRAC-I\",0,0,\"Prac-I\",\"Ions:PFRAC\",PERCENT",
"DATATYPE,\"/SRF:GROUP-I\",0,0,\"SrfGroup-I\",\"Ions:Surface Group\",SRFGROUP",
"DATATYPE,\"/SRF:AMH-I\",0,0,\"AMH-I\",\"Ions:AMH Classification\",AMH",
"DATATYPE,\"/SRF:ALL-W\",0,0,\"Srf-All-W\",\"Waters:Surface Area\",SRFALL",
"DATATYPE,\"/SRF:ALL%-W\",0,0,\"Srf-All%-W\",\"Waters:Surface Area %\",PERCENT",
"DATATYPE,\"/SRF:SID%-W\",0,0,\"Srf-Side-W\",\"Waters: Sidechain Pct\",PERCENT",
"DATATYPE,\"/SRF:BUR-W\",0,0,\"Srf-Buried-W\",\"Waters:Buried Area\",SRFBUR",
"DATATYPE,\"/SRF:PFRAC-W\",0,0,\"Pfrac-W\",\"Waters:PFRAC\",PERCENT",
"DATATYPE,\"/SRF:GROUP-W\",0,0,\"SrfGroup-W\",\"Waters:Surface Group\",SRFGROUP",
"DATATYPE,\"/SRF:AMH-W\",0,0,\"AMH-W\",\"Waters:AMH Classification\",AMH"
};

#else



char * SCMIEMBL[] = {

"COLORMAP,EMBLESH,\"sheet\",E,255,255,0,0",
"COLORMAP,EMBLESH,\"no pred\", ,255,255,255,0",
"COLORMAP,EMBLESH,\"helix\",H,240,0,128,0",

"COLORMAP,PPPHDHTM,\"Helical Tr.\",H,0,0,255,1",
"COLORMAP,PPPHDHTM,\"No Pred\", ,255,255,255,0",

"COLORMAP,PPSUBHTM,\"Helical Tr.\",H,0,0,255,1",
"COLORMAP,PPSUBHTM,\"No Pred\",.,255,255,255,0",
"COLORMAP,PPSUBHTM,\"Loop\",L,255,0,0,1",

"COLORMAP,EMBL0T9,\"0\",0,0,31,255,1",
"COLORMAP,EMBL0T9,\"1\",1,0,95,255,1",
"COLORMAP,EMBL0T9,\"2\",2,0,191,255,1",
"COLORMAP,EMBL0T9,\"3\",3,0,255,255,1",
"COLORMAP,EMBL0T9,\"4\",4,0,255,95,1",
"COLORMAP,EMBL0T9,\"5\",5,0,255,0,0",
"COLORMAP,EMBL0T9,\"6\",6,127,255,0,0",
"COLORMAP,EMBL0T9,\"7\",7,223,255,0,0",
"COLORMAP,EMBL0T9,\"8\",8,223,159,0,0",
"COLORMAP,EMBL0T9,\"9\",9,255,63,0,1",

"COLORMAP,PPP_3ACC,\"0-9%\",b,0,0,255,1",
"COLORMAP,PPP_3ACC,\"9-36%\", ,255,255,255,0",
"COLORMAP,PPP_3ACC,\"36-100%\",e,255,0,0,1",

"COLORMAP,PPSUBACC,\"0-9%\",b,0,0,255,1",
"COLORMAP,PPSUBACC,\"9-36%\",.,255,255,255,0",
"COLORMAP,PPSUBACC,\"36-100%\",e,255,0,0,1",

"COLORMAP,PPSUBSEC,\"Helix\",H,240,0,128,1",
"COLORMAP,PPSUBSEC,\"Sheet\",E,255,255,0,0",
"COLORMAP,PPSUBSEC,\"no pred\",.,255,255,255,0",
"COLORMAP,PPSUBSEC,\"Loop\",L,96,128,255,1",

"COLORMAP,DSSP,\"Alpha Helix\",H,240,0,128,1",
"COLORMAP,DSSP,\"Beta Bridge Residue\",B,0,255,255,1",
"COLORMAP,DSSP,\"Extended Strand\",E,255,255,0,0",
"COLORMAP,DSSP,\"3/10-Helix\",G,238,130,238,1",
"COLORMAP,DSSP,\"5-Helix\",I,128,0,0,1",
"COLORMAP,DSSP,\"H-bonded Turn\",T,0,0,255,1",
"COLORMAP,DSSP,\"Bend\",S,96,128,255,1",
"COLORMAP,DSSP,\"-\",-,255,255,255,0",

"DATATYPE,\"PHD sec |\",0,0,\"PP PHD SEC\",\"Prot Pred - Structure Prediction\",EMBLESH",
"DATATYPE,\"Rel sec |\",0,0,\"PP REL SEC\",\"Prot Pred - Structure Reliability\",EMBL0T9",
"DATATYPE,\"prH sec |\",0,0,\"PP PRH SEC\",\"Prot Pred - Probability Helix\",EMBL0T9",
"DATATYPE,\"prE sec |\",0,0,\"PP PRE SEC\",\"Prot Pred - Probability Sheet\",EMBL0T9",
"DATATYPE,\"prL sec |\",0,0,\"PP PRL SEC\",\"Prot Pred - Probability Loop\",EMBL0T9",
"DATATYPE,\"SUB sec |\",0,0,\"PP SUB SEC\",\"Prot Pred - Sub Structure\",PPSUBSEC",
"DATATYPE,\"P_3 acc |\",0,0,\"PP P_3 ACC\",\"Prot Pred - Solvent Accessibility in 3 states\",PPP_3ACC",
"DATATYPE,\"PHD acc |\",0,0,\"PP PHD ACC\",\"Prot Pred - Solvent Accessibility\",EMBL0T9",
"DATATYPE,\"Rel acc |\",0,0,\"PP REL ACC\",\"Prot Pred - Solvent Reliability\",EMBL0T9",
"DATATYPE,\"SUB acc |\",0,0,\"PP SUB ACC\",\"Prot Pred - Sub Solvent Accessibility\",PPSUBACC",
"DATATYPE,\"PHD htm |\",0,0,\"PP PHD HTM\", \"Prot Pred - Helical Transmembrane Region\",PPPHDHTM",
"DATATYPE,\"Rel htm |\",0,0,\"PP REL HTM\", \"Prot Pred - Helical Trans. Reliability\",EMBL0T9",
"DATATYPE,\"prH htm |\",0,0,\"PP PRH HTM\", \"Prot Pred - Helical Trans. Probability\",EMBL0T9",
"DATATYPE,\"prL htm |\",0,0,\"PP PRL HTM\", \"Prot Pred - Loop Probability\",EMBL0T9",
"DATATYPE,\"SUB htm |\",0,0,\"PP SUB HTM\", \"Prot Pred - Sub Helical Trans.\",PPSUBHTM",
"DATATYPE,\"Pred SS |\",0,0,\"Pred SS\",\"SS Pred - Prediction\",EMBLESH",
"DATATYPE,\"Clean SS|\",0,0,\"Clean SS\",\"SS Pred - Clean Prediction\",EMBLESH",
"DATATYPE,\"PREDATOR\",0,0,\"Predator\",\"Predator - Prediction\",EMBLESH",
"DATATYPE,\"/2_STR:DSS\",0,0,\"DSSP\",\"Secondary Structure -- DSSP\",DSSP",
};

char * SCMIPDB[] = {

"COLORMAP,PDB,\"Helix\",H,240,0,128,1",
"COLORMAP,PDB,\"Turn\",T,0,0,255,1",
"COLORMAP,PDB,\"Sheet\",S,255,255,0,0",

"DATATYPE,\"PDB\",0,0,\"PDB\",\"Secondary Structure -- PDB\",PDB",
};


#endif

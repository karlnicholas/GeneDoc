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
#ifndef PWALIGN_H_INCLUDED
#define PWALIGN_H_INCLUDED

class CAlignSeq;

class COverlap {
public:
	CAlignSeq *SeqId1;
	CAlignSeq *SeqId2;
	int Score;
	COverlap *Next;
	COverlap() {}
};

class CAlignSeq {
	CGeneSegment* pCGSeg;
	DWORD Begin;
	DWORD End;
public:
	void* Group;
	COverlap *List;
	CAlignSeq() {}
	CAlignSeq(CGeneSegment* npCGSeg) {
		List = NULL;
		pCGSeg = npCGSeg;
		pCGSeg->LockAndLoad();
		DWORD len = pCGSeg->GetTextLength();
		Begin = 0;
		End = len;

	}
	~CAlignSeq() { 
		pCGSeg->AlignDone();
		while ( List != NULL ) {
			COverlap *Save = List->Next;
			delete List;
			List = Save;
		}
	}
	inline int GetLength() {
		return (int)pCGSeg->GetTextLength();
	}
	inline BOOL Inside( DWORD Index ) {
		Index = Index - 1;
		return ( Index >= Begin && Index <= End );
	}
	inline void InsertDash( DWORD Index );
	inline char AlignGet( DWORD Index ) {
		return Index == 0? ' ' : Index > pCGSeg->GetTextLength() ? ' ' : pCGSeg->AlignGet(Index-1);
	}

};


class CAlign {
public:
	CPtrArray Sequences;
	DWORD MaxLen;		// maximum of sequence lengths
	int NewSeqs;
	CAlign() { MaxLen = 0; EdgeNum = 0; }
	void AddSequence( CGeneSegment* pCGSeg ) {
		CAlignSeq *pSeq = new CAlignSeq( pCGSeg );
		Sequences.Add( pSeq );
		DWORD len = pSeq->GetLength();
		if ( len > MaxLen ) MaxLen = len;
	}
	int EdgeNum;
	~CAlign() {
		for ( int i=0; i < Sequences.GetSize(); ++i ) {
			delete (CAlignSeq*)Sequences[i];
		}
	}
};

class CScore {
public:
	int MaxMatch, MaxMismatch;	// max and min substitution weights
	int ScoreArray[128][128];	// substitution scores
	int GapOpen;	// q
	int GapExtend;	// r gap penalties
	int OpenPlusExtend;		// qr = q + r
	int GapLen;				// minimum length for constant-cost insertion
	int Pay;					// constant-cost for long insertion

//
	int SCORE;	// score of a best alignment
	int STARI;	// start row number
	int STARJ;	// start column number
	int ENDI;	// end row number
	int ENDJ;	// end column number

};

class CMultAl {

	// Perform pair-wise comparisons of sequences.

	CPtrArray Edge;
	CAlign Align;
	CScore Score;
//	CMultAl MultAl;

	// The following definitions are for function diff()

	#define gap(k)  ((k) <= 0 ? 0 : Score.GapOpen+Score.GapExtend*(k))	// k-symbol indel score
	#define gap2(k)  ((k) <= 0 ? 0 : ((k) <= Score.GapLen ? Score.GapOpen+Score.GapExtend*(k) : Score.Pay))
	// k-symbol insertion score

	CUIntArray CC;			// saving matrix scores
	CUIntArray DD;
	CUIntArray RR;			// saving start-points
	CUIntArray SS;
	CUIntArray S;				// saving operations for diff


	int sapp;				// Current script append ptr
	int last;				// Last script op appended


	// Append "Delete k" op
	inline void DEL(int k) {
		if (last < 0) {
			S[sapp-1] = last =  S[sapp-1] - (k);
		} else {
			last = -(k);
			S.SetAtGrow(sapp++, last);
		}
	}
	// Append "Insert k" op
	inline void INS(int k) {
		if (last > 0) {
			S[sapp-1] = last =  S[sapp-1] + (k);
		} else {
			last =  k;
			S.SetAtGrow(sapp++, k);
		}
	}

	// Append "Replace" op
	inline void REP()
	{
			last =  0;
			S.SetAtGrow(sapp++, 0);
	}

public:


	// Construct mutiple alignments
	void MAlign( CAlign& Align );

	// Construct mutiple alignments
	void MAlign2( 
		CPtrArray& Align1, 
		CPtrArray& Align2, 
		int MaxLen );
	// Merge two sequence alignment according to script S
	void Merge( CPtrArray& Align1, CPtrArray& Align2 );
	int diff( 
		CPtrArray &Align1, 
		CPtrArray &Align2, 
		int Length1, int Length2, 
		int tb, int te, int mm, int nn, int sc, int sr, int ec, int er );
	void Pairwise(CAlign& Align);
	void BigPass( CAlignSeq *A, CAlignSeq *B );
	int PWAlign(CGenedocDoc *pDoc);
};


#endif

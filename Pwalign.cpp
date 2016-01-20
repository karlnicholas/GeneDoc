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

#include "stdafx.h"

inline void CAlignSeq::InsertDash( DWORD Index ) {

/*	//	Sequence = Sequence.Left(Index) + '-' + Sequence.Mid(Index);
	GlobalUnlock( pCGSeg->GetTextHandle() );

	if ( Index < pCGSeg->GetTextLength() ) {
		pCGSeg->SlideText( Index, 1 );
		if ( !pCGSeg->m_Expanded ) {
			pCGSeg->AppendFiller(1);
		}
	} else {
		pCGSeg->AppendFiller(1);
	}

	pGS = (GeneStor *)GlobalLock( pCGSeg->GetTextHandle() );
*/
	pCGSeg->AlignInsertDash( Index );
	if ( Index <= Begin ) {
		Begin++;
	}
	if ( Index <= End ) {
		End++;
	}
}

// Construct mutiple alignments
void CMultAl::MAlign( CAlign& Align )
{

	COverlap *Node1;	// temporary pointer
	int i, j, sorted, k;

	Pairwise(Align);

	for ( i = 0; i < Align.Sequences.GetSize(); i++ ) {
		((CAlignSeq*)Align.Sequences[i])->Group = (void *)i;
	}

	for ( j = 0, i = 0; i < Align.Sequences.GetSize(); i++ ) {
		for ( Node1 = ((CAlignSeq*)Align.Sequences[i])->List; Node1 != NULL; Node1 = Node1->Next ) {
			Edge.Add(Node1);
			j++;
		}
	}
	Align.EdgeNum = j;

	for ( i = Align.EdgeNum - 1; i > 0; i-- ) {
		sorted = 1;
		for ( j = 0; j < i; j++ ) {
			if ( ((COverlap*)Edge[j])->Score < ((COverlap*)Edge[j+1])->Score ) {
				Node1 = (COverlap*)Edge[j];
				Edge[j] = Edge[j+1];
				Edge[j+1] = Node1;
				sorted = 0;
			}
		}
		if ( sorted ) break;
	}
	
	typedef CPtrArray SeqPtrArray;

	SeqPtrArray *Align1;
	SeqPtrArray *Align2;
     
	// Collection
	CMapPtrToPtr BuildAlign;

	for ( k = 0; k < Align.EdgeNum; k++ ) {
		CAlignSeq* Seq1 = ((COverlap*)Edge[k])->SeqId1;
		CAlignSeq* Seq2 = ((COverlap*)Edge[k])->SeqId2;
		if ( Seq1->Group != Seq2->Group ) {
			if ( !BuildAlign.Lookup ( Seq1->Group, (void*&)Align1) ) {
				Align1 = new SeqPtrArray();
				Align1->Add( Seq1 );
			}
			if ( !BuildAlign.Lookup ( Seq2->Group, (void*&)Align2 ) ) {
				Align2 = new SeqPtrArray();
				Align2->Add( Seq2 );
			}
			if ( ((CAlignSeq*)(*Align1)[0])->GetLength() > ((CAlignSeq*)(*Align2)[0])->GetLength() ) {
				SeqPtrArray* t = Align1;
				Align1 = Align2;
				Align2 = t;
			}
			DD.SetSize(((CAlignSeq*)(*Align2)[0])->GetLength() + 2);
			RR.SetSize(((CAlignSeq*)(*Align2)[0])->GetLength() + 2);
			SS.SetSize(((CAlignSeq*)(*Align2)[0])->GetLength() + 2);
			CC.SetSize(((CAlignSeq*)(*Align2)[0])->GetLength() + 2);
			DD[0] = 0;
			RR[0] = 0;
			SS[0] = 0;
			CC[0] = 0;
			sapp = 0;
			last = 0;
			diff(*Align1, *Align2, 
				((CAlignSeq*)(*Align1)[0])->GetLength(), ((CAlignSeq*)(*Align2)[0])->GetLength(), 
				Score.GapOpen, Score.GapOpen,0,0,0,0,0,0
			);
			Merge(*Align1, *Align2);
//				(*Align1).Append( *Align2 );
			for ( i=0; i < (*Align2).GetSize(); ++i ) {
				Align1->Add((*Align2)[i]);
			}
			for ( i=0; i < (*Align1).GetSize(); ++i ) {
				((CAlignSeq*)(*Align1)[i])->Group = Align1;
			}
			BuildAlign.RemoveKey(Align2 );
			delete Align2;
//				BuildAlign.SetAt( (*Align1)[0], Align1 );
			if ( !BuildAlign.Lookup( &Align1, (void*&)Align2 ) ) {
				BuildAlign.SetAt( Align1, (void*&)Align1 );
			}
		}
	}
	POSITION Pos = BuildAlign.GetStartPosition();
	while ( Pos != NULL ) {
		void* p;
		BuildAlign.GetNextAssoc(Pos, p, (void*&)Align1);
		delete Align1;
	}
//		BuildAlign.RemoveAll();

}

// Construct mutiple alignments
void CMultAl::MAlign2( 
	CPtrArray& Align1, 
	CPtrArray& Align2, 
	int MaxLen )
{


	DD.SetSize(MaxLen + 2);
	RR.SetSize(MaxLen + 2);
	SS.SetSize(MaxLen + 2);
	CC.SetSize(MaxLen + 2);
	DD[0] = 0;
	RR[0] = 0;
	SS[0] = 0;
	CC[0] = 0;

	sapp = 0;
	last = 0;

	diff(Align1, Align2, 
		((CAlignSeq*)Align1[0])->GetLength(), ((CAlignSeq*)Align2[0])->GetLength(), 
		Score.GapOpen, Score.GapOpen,0,0,0,0,0,0
	);
	Merge(Align1, Align2);
}


// Merge two sequence alignment according to script S
// int	head1, int head2;	// ids of first sequences in two alignments
void CMultAl::Merge( CPtrArray& Align1, CPtrArray& Align2 )
{
	int	size1, size2;	// number of sequences in two alignments
	int	i, j, h, k;	// index variables
	int	op;		// current script operation
	int M, N;

	int Sat = 0;

	size1 = Align1.GetSize();
	size2 = Align2.GetSize();

	k = 0;
	M = ((CAlignSeq*)Align1[0])->GetLength();
	N = ((CAlignSeq*)Align2[0])->GetLength();
	op = 0;
	i = 0;
	j = 0;

	while (i < M || j < N) {
		if (op == 0 && S[Sat] == 0) {
			op = S[Sat++];
			++i;
			++j;
		} else {
			if (op == 0)
				op = S[Sat++];
			if (op > 0) {
				for ( h = 0; h < size1; h++ ) {
					((CAlignSeq*)Align1[h])->InsertDash(k);
				}
				++j;
				op--;
			} else {
				++i;
				for ( h = 0; h < size2; h++ ) {
					((CAlignSeq*)Align2[h])->InsertDash(k);
				}
				
				op++;
			}
		}
		k++;
	}
}

// diff(A,B,M,N,tb,te,U,W,mm,nn,sc,sr,ec,er) returns the score of an optimum conversion
// between A[0..U-1][mm+1..mm+M] and B[0..W-1][nn+1..nn+N] that begins(ends) with
// a delete if tb(te) is zero and appends such a conversion to the current script.
// If sc = 0, then the beginning deletion is not penalized; if sr = 0, the beginning
// insertion is not penalized; if ec = 0, the ending deletion is not charged;
// if er = 0; then the ending insertion is not charged.  Any insertion of length
// at least gaplen is given a constant cost

int CMultAl::diff( 
	CPtrArray &Align1, 
	CPtrArray &Align2, 
	int Length1, int Length2, 
	int tb, int te, int mm, int nn, int sc, int sr, int ec, int er )
{
	int midi, midj;
	int type;	// Midpoint, type, and cost
	int midc;
	int ss,cc;

	int i, j;
	int c, e, d, s;
	int t, *pScoreArray;
	int  g, temp;
	int  h,k;			// index variables
	int  tt;			// temporary variable
	int  x,y;			// number of non-blank symbols in columns

// Boundary cases: M <= 1 or N == 0

	if (Length2 <= 0) {
		if (Length1 > 0) 
			DEL(Length1);
		if ( !sc || !ec )
			return 0;
		else
			return - gap((int)Length1);
	}
	if (Length1 <= 1) {
		if (Length1 <= 0) {
			INS(Length2);
			if ( !sr || !er )
				return 0;
			else
				return - gap2((int)Length2);
		}
		midc = - (sc * (tb + Score.GapExtend) + er * gap2(Length2) );
		midj = -1;
		if ( midc < ( c =  - (ec * (te + Score.GapExtend) + sr * gap2(Length2) ) ) ) {
			midc = c;
			midj = 0;
		}
		for ( x = h = 0; h < Align1.GetSize(); h++ ) {
			if ( ((CAlignSeq*)Align1[h])->Inside(mm+1) )
				x += 1;
		}
		for (j = 1; j <= Length2; j++) {
			c = 0;
			for ( h = 0; h < Align1.GetSize(); h++ ) {
				tt = ((CAlignSeq*)Align1[h])->AlignGet(mm+1);
				if ( ((CAlignSeq*)Align1[h])->Inside(mm+1) ) {
					pScoreArray = Score.ScoreArray[toupper(tt)];
					for ( k = 0; k < Align2.GetSize(); k++ ) {
						tt = ((CAlignSeq*)Align2[k])->AlignGet(nn+j);
						if ( ((CAlignSeq*)Align2[k])->Inside(nn+j) ) 
							c += pScoreArray[toupper(tt)];
					}
				}
			}
			for ( y = k = 0; k < Align2.GetSize(); k++ )
				if ( ((CAlignSeq*)Align2[k])->Inside(nn+j) )
					y += 1;
			c = c / (x * y) - ( sr * gap2(j-1) + er * gap2(Length2-j) );
			if (c > midc) {
				midc = c;
				midj = j;
			}
		}
		if (midj == -1) {
			DEL(1);
			INS(Length2);
		} else if (midj == 0) {
			INS(Length2);
			DEL(1);
		} else {
			if (midj > 1) 
				INS(midj-1);
			REP();
			if (midj < Length2) 
				INS(Length2-midj);
		}
		return midc;
	}

	// Divide: Find optimum midpoint (midi,midj) of cost midc

	midi = Length1/2;			// Forward phase:                         
	CC[0] = 0;			//   Compute C(Length1/2,k) & D(Length1/2,k) for all k
	t = -Score.GapOpen * sr;
	if ( Length2 <= Score.GapLen ) {
		for (j = 1; j <= Length2; j++) {
			CC[j] = t = (t-Score.GapExtend) * sr;
			DD[j] = t - Score.GapOpen;
		}
	} else {
		for (j = 1; j <= Score.GapLen; j++) {
			CC[j] = t = (t-Score.GapExtend) * sr;
			DD[j] = t - Score.GapOpen;
		}
		for (j = Score.GapLen+1; j <= Length2; j++) {
			CC[j] = t = -Score.Pay * sr;
			DD[j] = t - Score.GapOpen;
		}
	}
	if ( !ec ) DD[Length2] += Score.GapOpen;
	t = -tb * sc;
	for (i = 1; i <= midi; i++) {
		s = CC[0];
		CC[0] = c = t = (t-Score.GapExtend) * sc;
		e = t - Score.GapOpen;
		g = t - Score.Pay;
		for ( x = h = 0; h < Align1.GetSize(); h++ ) {
			if ( ((CAlignSeq*)Align1[h])->Inside(mm+i) ) {
				x += 1;
			}
		}
		for (j = 1; j <= Length2; j++) {
			if ((c = c - Score.OpenPlusExtend) > (e = e - Score.GapExtend)) e = c;
			if ( j == Length2 && !ec ) {
				if ((c = CC[j] ) > (d = DD[j] )) d = c;
			} else if ((c = CC[j] - Score.OpenPlusExtend) > (d = DD[j] - Score.GapExtend)) d = c;
			c = 0;
			for ( h = 0; h < Align1.GetSize(); h++ ) {
				tt = ((CAlignSeq*)Align1[h])->AlignGet(mm+i);
				if ( ((CAlignSeq*)Align1[h])->Inside(mm+i) ) {
					pScoreArray = Score.ScoreArray[toupper(tt)];
					for ( k = 0; k < Align2.GetSize(); k++ ) {
						tt = ((CAlignSeq*)Align2[k])->AlignGet(nn+j);
						if ( ((CAlignSeq*)Align2[k])->Inside(nn+j) )
							c += pScoreArray[toupper(tt)];
					}
				}
			}
			for ( y = k = 0; k < Align2.GetSize(); k++ ) {
				if ( ((CAlignSeq*)Align2[k])->Inside(nn+j) ) {
					y += 1;
				}
			}
			c = c / (x * y) + s;
			if (c < d) c = d;
			if (c < e) c = e;
			if ( j - Score.GapLen > 0 ) {
				if ( g < ( temp = CC[j-Score.GapLen-1] - Score.Pay ) )
					g = temp;
				if ( c < g ) c = g;
			}
			s = CC[j];
			CC[j] = c;
			DD[j] = d;
		}
	}
	DD[0] = CC[0];

	RR[Length2] = 0;			// Reverse phase:                         
	t = -Score.GapOpen * er;			//   Compute R(Length1/2,k) & S(Length1/2,k) for all k
	if ( Length2 <= Score.GapLen )
		for (j = Length2-1; j >= 0; j--) {
			RR[j] = t = (t-Score.GapExtend) * er;
			SS[j] = t-Score.GapOpen;
		}
	else {
		temp = Length2 - Score.GapLen;
		for (j = Length2-1; j >= temp; j--) {
			RR[j] = t = (t-Score.GapExtend) * er;
			SS[j] = t-Score.GapOpen;
		}
		for (j = temp-1; j >= 0; j--) {
			RR[j] = t = -Score.Pay * er;
			SS[j] = t - Score.GapOpen;
		}
	}
	if ( !sc ) SS[0] += Score.GapOpen;
	t = -te * ec;
	for (i = Length1-1; i >= midi; i--) {
		s = RR[Length2];
		RR[Length2] = c = t = (t-Score.GapExtend) * ec;
		g = t - Score.Pay;
		e = t - Score.GapOpen;
		for ( x = h = 0; h < Align1.GetSize(); h++ ) {
			if ( ((CAlignSeq*)Align1[h])->Inside(mm+i+1) )
				x += 1;
		}
		for (j = Length2-1; j >= 0; j--) {
			if ((c = c - Score.OpenPlusExtend) > (e = e - Score.GapExtend)) e = c;
			if ( !j && !sc ) {
				if ((c = RR[j] ) > (d = SS[j] )) d = c;
			} else if ((c = RR[j] - Score.OpenPlusExtend) > (d = SS[j] - Score.GapExtend)) 
				d = c;
			c = 0;
			for ( h = 0; h < Align1.GetSize(); h++ ) {
				tt = ((CAlignSeq*)Align1[h])->AlignGet(mm+i+1);
				if ( ((CAlignSeq*)Align1[h])->Inside(mm+i+1) ) {
					pScoreArray = Score.ScoreArray[toupper(tt)];
					for ( k = 0; k < Align2.GetSize(); k++ ) {
						tt = ((CAlignSeq*)Align2[k])->AlignGet(nn+j+1);
						if ( ((CAlignSeq*)Align2[k])->Inside(nn+j+1) )
							c += pScoreArray[toupper(tt)];
					}
				}
			}
			for ( y = k = 0; k < Align2.GetSize(); k++ ) {
				if ( ((CAlignSeq*)Align2[k])->Inside(nn+j+1) )
					y += 1;
			}
			c = c / (x * y) + s;
			if (c < d) c = d;
			if (c < e) c = e;
			if ( j + Score.GapLen < Length2 ) {
				if ( g < ( temp = RR[j+Score.GapLen+1] - Score.Pay ) )
					g = temp;
				if ( c < g ) c = g;
			}
			s = RR[j];
			RR[j] = c;
			SS[j] = d;
		}
	}
	SS[Length2] = RR[Length2];

	midc = CC[0]+RR[0];		// Find optimal midpoint
	midj = 0;
	type = 1;
	for (j = 0; j <= Length2; j++)
		if ((c = CC[j] + RR[j]) >= midc)
			if (c > midc || CC[j] != DD[j] && RR[j] == SS[j]) {
				midc = c;
				midj = j;
			}
	for (j = Length2; j >= 0; j--) {
		if ( j == Length2 )
			d = Score.GapOpen * ec;
		else if ( j == 0 )
			d = Score.GapOpen * sc;
		else
			d = Score.GapOpen;
		if ((c = DD[j] + SS[j] + d) > midc) {
			midc = c;
			midj = j;
			type = 2;
		}
	}


// Conquer: recursively around midpoint

	cc = midj == Length2 ? ec : 1;
	ss = midj == 0 ? sc : 1;
	if (type == 1) {
		diff(Align1,Align2,midi,midj,tb,Score.GapOpen,mm,nn,sc,sr,cc,1);
		diff(Align1,Align2,Length1-midi,Length2-midj,Score.GapOpen,te,mm+midi,nn+midj,ss,1,ec,er);
	} else {
		diff(Align1,Align2,midi-1,midj,tb,0,mm,nn,sc,sr,cc,1);
		DEL(2);
		diff(Align1,Align2,Length1-midi-1,Length2-midj,0,te,mm+midi+1,nn+midj,ss,1,ec,er);
	}
	return midc;
}

// Perform pair-wise comparisons of sequences.
// total = total sequence length;
void CMultAl::Pairwise(CAlign& Align)
{
	COverlap *Node1;

	for ( int i = 0; i < Align.Sequences.GetSize() - 1 ; i++ ) {
		CAlignSeq* A = (CAlignSeq*)Align.Sequences[i];
		for ( int j = i+1; j < Align.Sequences.GetSize() ; j++ ) {
			CAlignSeq* B = (CAlignSeq*)Align.Sequences[j];
			Node1 = new COverlap();
			Score.SCORE = - ( 2 * Score.GapOpen + ((int)A->GetLength() + (int)B->GetLength()) * Score.GapExtend + 1000);
			if ( A->GetLength() <= B->GetLength() ) {
				BigPass( A,B );
				Node1->SeqId1 = A;
				Node1->SeqId2 = B;
				Node1->Score = Score.SCORE;
				Node1->Next = A->List;
				A->List = Node1;
			} else {
				BigPass( B,A );
				Node1->SeqId1 = B;
				Node1->SeqId2 = A;
				Node1->Score = Score.SCORE;
				Node1->Next = B->List;
				B->List = Node1;
			}
			Align.EdgeNum++;
		}
	}
}

// find best overlap score between two sequences 
void CMultAl::BigPass( CAlignSeq *A, CAlignSeq *B )
{
	int j;
	int  i;			// row and column indices 
	int  c;			// best score at current point 
	int  f;			// best score ending with insertion 
	int  d;			// best score ending with deletion 
	int  p;			// best score at (i-1, j-1) 
	int  ci;		// end-point associated with c  
	int  di;		// end-point associated with d 
	int  fi;		// end-point associated with f 
	int  pi;		// end-point associated with p 
	int  g;			// best score ending with constant-cost insertion 
	int  gi;		// end-point associated with g 
	int  t;			// temporary variable 
	int  *pScoreArray;		// pointer to v(A[i], B[j]) 

	CC.RemoveAll();
	DD.RemoveAll();
	RR.RemoveAll();
	SS.RemoveAll();

	CC.Add(0);
	DD.Add(0);
	RR.Add(0);
	SS.Add(0);

	for ( j = 1; j <= (int)B->GetLength(); j++ )
	{
		CC.Add(0);
		DD.Add(- (Score.GapOpen));
		RR.Add(-j);
		SS.Add(-j);
	}


	for ( i = 1; i <= (int)A->GetLength(); i++) 
	{
		c = 0;				// Initialize column 0 
		f = - (Score.GapOpen);
		g = - Score.Pay;
		ci = fi = gi = i;
		p = 0;
		pi = i - 1;
		pScoreArray = Score.ScoreArray[toupper(A->AlignGet(i))];
		for ( j = 1; j <= (int)B->GetLength(); j++ )  {
			if ( ( f = f - Score.GapExtend ) < ( c = c - Score.OpenPlusExtend ) ) {
				f = c; fi = ci;
			}
			di = SS[j];
			if ( ( d = DD[j] - Score.GapExtend ) < ( c = CC[j] - Score.OpenPlusExtend ) ) {
				d = c; di = RR[j];
			} 
			c = p+pScoreArray[toupper(B->AlignGet(j))];		// diagonal 
			ci = pi;
			if ( c < d ) {
				c = d; ci = di;
			}
			if ( c < f ) {
				c = f; ci = fi;
			}
			if ( j - Score.GapLen > 0 ) {
				if ( g < ( t = CC[j-Score.GapLen-1] - Score.Pay ) ) {
					g = t; gi = RR[j-Score.GapLen-1];
				}
				if ( c < g ) {
					c = g; ci = gi;
				}
			}
			p = CC[j];
			CC[j] = c;
			pi = RR[j];
			RR[j] = ci;
			DD[j] = d;
			SS[j] = di;
			if ( ( j == (int)B->GetLength() || i == (int)A->GetLength() ) &&  c > Score.SCORE ) {
				Score.SCORE = c;
				Score.ENDI = i;
				Score.ENDJ = j;
				Score.STARI = ci;
			}
		}
	}
	if ( Score.STARI < 0 ) {
		Score.STARJ = - Score.STARI;
		Score.STARI = 0;
	} else {
		Score.STARJ = 0;
	}
}


int CMultAl::PWAlign(CGenedocDoc *pDoc)
{
	int i, j;

	CAlignDlg aDlg;
	aDlg.pDoc = pDoc;
	aDlg.m_GapLen = 20;
	aDlg.m_GapOpen = NewGap - CurrentZeroDistance;
	aDlg.m_GapExtend = GapLen - CurrentZeroDistance;

	if ( aDlg.DoModal() != IDOK ) return 0;

	pDoc->BeginWaitCursor();
	if ( !aDlg.m_AlignMeth ) {
		POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {

			CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);

			if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;

			if ( tCGSeg->GetExportFlag()  ) continue;
		
			Align.AddSequence( tCGSeg );
		}
		if ( Align.Sequences.GetSize() == 0 ) {
			AfxMessageBox("You need to have at least one sequence not selected in this mode!");
			return 0;
		}
	}
	Align.NewSeqs = Align.Sequences.GetSize();

	if ( aDlg.m_DeGap ) {
		CGeneSegment *tCGSeg;
		int isok;
		
		POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
		while (tPos != NULL ) {

			CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);
			if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;
			if ( !tCGSeg->GetExportFlag()  ) continue;
		
			DWORD Size = tCGSeg->GetTextLength() - 1;
			GeneStor *pc = (GeneStor *)GlobalLock(tCGSeg->GetTextHandle());
			pc += Size;
		
			while ( Size ) {
				char tChar = toupper ( pc->CharGene );
				if ( (tChar >= 'A' && tChar <= 'Z') ) break;
				pc--;
				Size--;
			}
			GlobalUnlock(tCGSeg->GetTextHandle());
			tCGSeg->MoveText( Size, 0 - Size );
		}


		tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetHead();
		DWORD dwLen = tCGSeg->GetTextLength();

		for ( DWORD dwCount = 0; dwCount < dwLen; ++dwCount ) {

			POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
			while (tPos != NULL ) {
				tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);
				if ( !tCGSeg->GetExportFlag()  ) continue;
				isok = tCGSeg->TestDeleteFillerRange( dwCount, dwCount );
				if ( !isok ) break;
			}

			if ( isok ) {
				tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
				while (tPos != NULL ) {
					tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);
					if ( !tCGSeg->GetExportFlag()  ) continue;
					tCGSeg->DeleteFillerRange( dwCount, dwCount );
				}

				dwLen--;
				dwCount--;
			}
		}

	}

	POSITION tPos = pDoc->pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {

		CGeneSegment *tCGSeg = (CGeneSegment *)pDoc->pGSFiller->SegDataList.GetNext(tPos);

		if ( tCGSeg->GetStyle() != LINESEQUENCE ) continue;

		if ( !tCGSeg->GetExportFlag()  ) continue;

		Align.AddSequence( tCGSeg );
	}


	if ( Align.Sequences.GetSize() == 0 ) {
		AfxMessageBox("You need to select at least one sequence!");
		return 0;
	}

	Score.GapLen = aDlg.m_GapLen;
	Score.GapOpen = aDlg.m_GapOpen;
	Score.GapExtend = aDlg.m_GapExtend;


	Score.Pay = Score.GapOpen + Score.GapExtend * Score.GapLen;
	Score.OpenPlusExtend = Score.GapOpen + Score.GapExtend;

	// check if the argument represents a negative integer 

	int Mismatch;				// User-supplied weights      

	if ( pDoc->m_UserVars.m_ProjectType > 1 ) {
		// DNA Case
		Score.MaxMatch = Score.MaxMismatch = 0;
		for ( i = 0; i < 128 ; i++ ) {
			for ( j = 0; j < 128 ; j++ ) {
				Score.ScoreArray[i][j] = 0;
			}
		}
		for ( i = 0; i < 16; ++i ) {
			char Char1 = DNALocArray[i];
			for ( j=0; j < 16; ++j ) {
				char Char2 = DNALocArray[j];
				Mismatch = CurrentZeroDistance - ScoreCurrentArray( Char1, Char2 );
				Score.ScoreArray[Char1][Char2] = Score.ScoreArray[Char2][Char1] = Mismatch;
				if ( Mismatch > Score.MaxMatch ) Score.MaxMatch = Mismatch;
				if ( Mismatch < Score.MaxMismatch ) Score.MaxMismatch = Mismatch;
			}
		}
	} else {
		// Protein case
		Score.MaxMatch = Score.MaxMismatch = 0;
		for ( i = 0; i < 128 ; i++ ) {
			for ( j = 0; j < 128 ; j++ ) {
				Score.ScoreArray[i][j] = 0;
			}
		}
		for ( i = 0; i < 23; ++i ) {
			char Char1 = ProteinLocArray[i];
			for ( j=0; j < 23; ++j ) {
				char Char2 = ProteinLocArray[j];
				Mismatch = CurrentZeroDistance - ScoreCurrentArray( Char1, Char2 );
				Score.ScoreArray[Char1][Char2] = Score.ScoreArray[Char2][Char1] = Mismatch;
				if ( Mismatch > Score.MaxMatch ) Score.MaxMatch = Mismatch;
				if ( Mismatch < Score.MaxMismatch ) Score.MaxMismatch = Mismatch;
			}
		}
	}

	for ( i = 0; i < 128 ; i++ ) {
		Score.ScoreArray['-'][i] = Score.ScoreArray[i]['-'] = - Score.GapExtend;
	}
	Score.ScoreArray['-']['-'] = 0;


	if ( aDlg.m_AlignMeth == 0 ) { 
		CPtrArray Align1;
		CPtrArray Align2;

		for ( int i = 0; i < Align.NewSeqs; i++ ) {
			Align1.Add( Align.Sequences[i] );
		}

		for ( i = Align.NewSeqs; i < Align.Sequences.GetSize(); i++ ) {
			Align2.Add( Align.Sequences[i] );
		}

		MAlign2(Align1, Align2, Align.MaxLen );
	} else {

		MAlign(Align);
	}

	pDoc->EndWaitCursor();
	return 1;
}


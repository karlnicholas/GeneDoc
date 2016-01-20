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

void
CGenedocDoc::ReScoreAll(int ScoreAll)
{
	if ( pGSFiller == NULL ) {
		return;
	}

	CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetHead();
	HANDLE tSegHandle = tCGSeg->GetTextHandle();
	GeneStor *pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
	if ( pGeneStor == NULL ) {
		AfxMessageBox("ReScoreAll:GlobalLock:Fail:1");
		return;
	}

	DWORD SegLength = tCGSeg->GetTextLength(); 

	DWORD StartRange = 0; 
	DWORD EndRange = 0;

	while ( StartRange < SegLength ) {

		if ( (pGeneStor[StartRange].CharScore > 0) && 
			( 
				( (pGeneStor[StartRange].CharScore%2) == 0 ) 
				|| ( ScoreAll ) 
			)
		) {
			GlobalUnlock( tSegHandle );
			if ( FindScore( StartRange, &StartRange, &EndRange ) ) {
				Score( &StartRange, &EndRange );
			}
			pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
			if ( pGeneStor == NULL ) {
				AfxMessageBox("ReScoreAll:GlobalLock:Fail:2");
				return;
			}
		}
		EndRange = StartRange = EndRange + 1;
	}
	
	GlobalUnlock( tSegHandle );
}


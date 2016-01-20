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

//***********************************************************************
// Function:
//
//     HeapSort()
//
// Purpose:
//
//     Implements the HeapSort sorting algorithm.
//
// Parameters:
//
//     void * - Not used but is required for thread entry point functions
//              for threads started with _beginthread().
//
// Returns:
//
//     void
//
// Comments:
//
//     HeapSort (also called TreeSort) works by calling PercolateUp and
//     PercolateDown. PercolateUp organizes the elements into a "heap"
//     or "tree," which has the properties shown below:
/*
                              element[1]
                            /            \
                 element[2]                element[3]
                /          \              /          \
          element[4]     element[5]   element[6]    element[7]
          /        \     /        \   /        \    /        \
         ...      ...   ...      ... ...      ...  ...      ...
*/
//     Each "parent node" is greater than each of its "child nodes"; for
//     example, element[1] is greater than element[2] or element[3];
//     element[4] is greater than element[5] or element[6], and so forth.
//     Therefore, once the first loop in HeapSort is finished, the
//     largest element is in element[1].
//
//     The second loop rebuilds the heap (with PercolateDown), but starts
//     at the top and works down, moving the largest elements to the
//     bottom. This has the effect of moving the smallest elements to the
//     top and sorting the heap.
//
// History:
//
//   Date   Comment                                           Initials
// ======== ================================================= ========
// 10/12/93 Created                                             JKK
//***********************************************************************

void PercolateUp( int iMaxLevel, double * pList );
void PercolateDown( int iMaxLevel, double * pList );

void HeapSort(double *pList, int cbLength )
{
	int i;
	double tmp;
    
	for( i = 1; i < cbLength; i++ ) {
		PercolateUp( i, pList );
	}

	for( i = cbLength - 1; i > 0; i-- ) {
		tmp = pList[0];
		pList[0] = pList[i];
		pList[i] = tmp;

		PercolateDown( i - 1, pList );

	}
}

//***********************************************************************
// Function:
//
//     PercolateUp()
//
// Purpose:
//
//     Converts elements into a "heap" with the largest element at the
//     top (see the diagram above).
//
// Parameters:
//
//     iMaxLevel - Specifies the list element being moved.
//     pList     - A pointer to the list to be sorted.
//
// Returns:
//
//     void
//
// History:
//
//   Date   Comment                                           Initials
// ======== ================================================= ========
// 10/12/93 Created                                             JKK
//***********************************************************************

void PercolateUp( int iMaxLevel, double * pList )
{
	int i = iMaxLevel, iParent;
	double tmp;

	// Move the value in pList[iMaxLevel] up the heap until it has
	// reached its proper node (that is, until it is greater than either
	// of its child nodes, or until it has reached 1, the top of the heap).

	while( i )
	{
		iParent = i / 2;    // Get the subscript for the parent node
		if( pList[i] > pList[iParent] )
		{
			// The value at the current node is bigger than the value at
			// its parent node, so swap these two array elements.
			//
			tmp = pList[iParent];
			pList[iParent] = pList[i];
			pList[i] = tmp;
			i = iParent;
		}
		else
			// Otherwise, the element has reached its proper place in the
			// heap, so exit this procedure.
			break;
	}
}

//***********************************************************************
// Function:
//
//     PercolateDown()
//
// Purpose:
//
//     Converts elements to a "heap" with the largest elements at the
//     bottom. When this is done to a reversed heap (largest elements at
//     top), it has the effect of sorting the elements.
//
// Parameters:
//
//     iMaxLevel - Specifies the list element being moved.
//     pList     - A pointer to the list to be sorted.
//
// Returns:
//
//     void
//
// History:
//
//   Date   Comment                                           Initials
// ======== ================================================= ========
// 10/12/93 Created                                             JKK
//***********************************************************************

void PercolateDown( int iMaxLevel, double * pList )
{
	int iChild, i = 0;
	double tmp;

	// Move the value in pList[0] down the heap until it has reached
	// its proper node (that is, until it is less than its parent node
	// or until it has reached iMaxLevel, the bottom of the current heap).

	while( TRUE )
	{
		// Get the subscript for the child node.
		iChild = 2 * i;

		// Reached the bottom of the heap, so exit this procedure.
		if( iChild > iMaxLevel )
			break;

		// If there are two child nodes, find out which one is bigger.
		if( iChild + 1 <= iMaxLevel )
		{
			if( pList[iChild + 1] > pList[iChild] )
				iChild++;
		}


		if( pList[i] < pList[iChild] )
		{
			// Move the value down since it is still not bigger than
			// either one of its children.
			tmp = pList[i];
			pList[i] = pList[iChild];
			pList[iChild] = tmp;

			i = iChild;
		}
		else
			// Otherwise, pList has been restored to a heap from 1 to
			// iMaxLevel, so exit.
			break;
	}
}

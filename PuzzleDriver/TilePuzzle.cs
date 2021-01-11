using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PuzzleDriver
{
	class TilePuzzle
	{
		MainForm mainForm;
		int nRows, nCols;
		int[,] tiles;

		public TilePuzzle(MainForm _mainForm, int _nRows, int _nCols, List<Button> tileButtonList)
		{
			mainForm = _mainForm;
			nRows = _nRows;
			nCols = _nCols;
			mainForm.Log("TilePuzzle({0}, {1})", nRows, nCols);
			tiles = new int[nRows, nCols];

			LoadArrayFromButtons(tileButtonList);
		}
		public bool LoadArrayFromButtons(List<Button> tileButtonList)
		{
			mainForm.Log("LoadArrayFromButtons(...)");
			if (tileButtonList.Count != nRows * nCols)
			{
				mainForm.Log("LoadArrayFromButtons: ListLength <> nRows*nCols");
				return false;
			}

			int idx = 0;
			for (int row = 0; row < nRows; row++)
				for (int col = 0; col < nCols; col++)
				{
					string label = tileButtonList[idx++].Text;
					int key = 0;
					if (label != "")
						key = Int32.Parse(label);
					tiles[row, col] = key;
					//Console.WriteLine("tiles[{0},{1}]={2}", row, col, key);
				}
			LoadButtonsFromArray(tileButtonList);
			return true;
		}
		public bool LoadButtonsFromArray(List<Button> tileButtonList)
		{
			mainForm.Log("LoadButtonsFromArray(...)");
			if (tileButtonList.Count != nRows * nCols)
			{
				mainForm.Log("LoadButtonsFromArray: ListLength <> nRows*nCols");
				return false;
			}

			int idx = 0;
			for (int row = 0; row < nRows; row++)
				for (int col = 0; col < nCols; col++)
				{
					tileButtonList[idx++].Text = tiles[row, col] == 0 ? "" : tiles[row, col].ToString();
					//Console.WriteLine("button[{0}]={1}", idx - 1, tileButtonList[idx - 1].Text);
				}

			return true;
		}
		public (int row, int col) FindTile(int tileNum)
		{
			for (int row = 0; row < nRows; row++)
				for (int col = 0; col < nCols; col++)
					if (tiles[row, col] == tileNum)
					{
						//Console.WriteLine("FindTile({0}) returns [{1}, {2}]", tileNum, row, col);
						return (row, col);
					}

			mainForm.Log("FindTile({0}) FAILED", tileNum);
			return (-1, -1);
		}
		public bool MoveTile(int tileNum)
		{
			mainForm.Log("MoveTile({0})", tileNum);

			// Find the tile of record and the blank
			var blankTile = FindTile(0);
			var thisTile = FindTile(tileNum);

			// Must be adjacent by 1 to be swappable
			int distance = Math.Abs(blankTile.row - thisTile.row) + Math.Abs(blankTile.col - thisTile.col);
			mainForm.Log("distance={0}", distance);

			if (distance != 1)
			{
				mainForm.Log("Can't move tile {0}", tileNum);
				return (false);
			}

			tiles[thisTile.row, thisTile.col] = 0;
			tiles[blankTile.row, blankTile.col] = tileNum;
			return true;
		}

		static Random MakeRandomMove_random = new Random();
		public bool MakeRandomMove(int nMoves = 1)
		{
			mainForm.Log("MakeRandomMove({0})", nMoves);
			int[] moveRow = new int[4];
			int[] moveCol = new int[4];

			for (int i = 0; i < nMoves; i++)
			{
				// Find the blank
				var blankTile = FindTile(0);

				// Tally up possible moves
				int nPossibleMoves = 0;

				// Can we move left?
				if (blankTile.col > 0)
				{
					moveRow[nPossibleMoves] = blankTile.row;
					moveCol[nPossibleMoves++] = blankTile.col - 1;
				}
				// Can we move right?
				if (blankTile.col < nCols - 1)
				{
					moveRow[nPossibleMoves] = blankTile.row;
					moveCol[nPossibleMoves++] = blankTile.col + 1;
				}
				// Can we move up?
				if (blankTile.row > 0)
				{
					moveRow[nPossibleMoves] = blankTile.row - 1;
					moveCol[nPossibleMoves++] = blankTile.col;
				}
				// Can we move down?
				if (blankTile.row < nRows - 1)
				{
					moveRow[nPossibleMoves] = blankTile.row + 1;
					moveCol[nPossibleMoves++] = blankTile.col;
				}
				//Console.WriteLine("MakeRandomMove can make {0} moves", nPossibleMoves);

				// Now pick one
				int idx = MakeRandomMove_random.Next(0, nPossibleMoves);

				// Swap!
				tiles[blankTile.row, blankTile.col] = tiles[moveRow[idx], moveCol[idx]];
				tiles[moveRow[idx], moveCol[idx]] = 0;
			}
			return true;
		}
	}
}

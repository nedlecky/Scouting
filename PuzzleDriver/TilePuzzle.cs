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
		int nRows, nCols;
		int[,] tiles;

		public TilePuzzle(int _nRows, int _nCols, List<Button> tileButtonList)
		{
			nRows = _nRows;
			nCols = _nCols;
			Console.WriteLine("TilePuzzle({0}, {1})", nRows, nCols);
			tiles = new int[nRows, nCols];

			LoadArrayFromButtons(tileButtonList);
		}
		public bool LoadArrayFromButtons(List<Button> tileButtonList)
		{
			if (tileButtonList.Count != nRows * nCols)
			{
				Console.WriteLine("LoadArrayFromButtons: ListLength <> nRows*nCols");
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
					Console.WriteLine("tiles[{0},{1}]={2}", row, col, key);
				}
			LoadButtonsFromArray(tileButtonList);
			return true;
		}
		public bool LoadButtonsFromArray(List<Button> tileButtonList)
		{
			if (tileButtonList.Count != nRows * nCols)
			{
				Console.WriteLine("LoadButtonsFromArray: ListLength <> nRows*nCols");
				return false;
			}

			int idx = 0;
			for (int row = 0; row < nRows; row++)
				for (int col = 0; col < nCols; col++)
				{
					tileButtonList[idx++].Text = tiles[row, col] == 0 ? "" : tiles[row, col].ToString();
					Console.WriteLine("button[{0}]={1}", idx - 1, tileButtonList[idx - 1].Text);
				}

			return true;
		}
		public (int row, int col) FindTile(int tileNum)
		{
			for (int row = 0; row < nRows; row++)
				for (int col = 0; col < nCols; col++)
					if (tiles[row, col] == tileNum)
					{
						Console.WriteLine("FindTile({0}) returns [{1}, {2}]", tileNum, row, col);
						return (row, col);
					}

			Console.WriteLine("FindTile({0}) FAILED", tileNum);
			return (-1, -1);
		}
		public bool MoveTile(int tileNum)
		{
			Console.WriteLine("MoveTile({0})", tileNum);

			// Find the tile of record and the blank
			var blankTile = FindTile(0);
			var thisTile = FindTile(tileNum);

			// Must be adjacent by 1 to be swappable
			int distance = Math.Abs(blankTile.row - thisTile.row) + Math.Abs(blankTile.col - thisTile.col);
			Console.WriteLine("distance={0}", distance);

			if (distance != 1)
			{
				Console.WriteLine("Can't move tile {0}", tileNum);
				return (false);
			}

			tiles[thisTile.row, thisTile.col] = 0;
			tiles[blankTile.row, blankTile.col] = tileNum;
			return true;
		}
	}
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PuzzleDriver
{
	public partial class MainForm : Form
	{
		public MainForm()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			Text = "PuzzleDriver 1.0";

			RowCountCombo.SelectedItem = "4";
			ColCountCombo.SelectedItem = "4";
			SetupBtn_Click(null, null);
		}

		TilePuzzle tilePuzzle;
		List<Button> tileButtonList = new List<Button>();
		private void CreateButtons(int nRows, int nCols)
		{
			int tileSize = 40;
			int startX = 120;
			int startY = 50;

			int tileID = 1;
			for (int row = 0; row < nRows; row++)
				for (int col = 0; col < nCols; col++)
				{
					Button newButton = new Button
					{
						Text = tileID++.ToString(),
						Location = new Point(startX + col*tileSize, startY + row*tileSize),
						Size = new Size(tileSize, tileSize),
						Visible = true
					};
					newButton.Click += new EventHandler(ButtonHandler);
					this.Controls.Add(newButton);
					tileButtonList.Add(newButton);
				}
			// Last tile gets the blank
			tileButtonList[tileButtonList.Count-1].Text = "";
			tilePuzzle = new TilePuzzle(nRows, nCols, tileButtonList);
		}

		private void ButtonHandler(object sender, EventArgs e)
		{
			int tileNum = 0;
			string label = ((Button)sender).Text;
			if (label != "")
				tileNum = Int32.Parse(label);
			Console.WriteLine("Button({0})", tileNum.ToString());
			tilePuzzle.MoveTile(tileNum);
		}

		private void ClearTiles()
		{
			foreach (Button button in tileButtonList)
			{
				this.Controls.Remove(button);
			}
			tileButtonList.Clear();
		}
		private void SetupBtn_Click(object sender, EventArgs e)
		{
			ClearTiles();
			CreateButtons(Int32.Parse(RowCountCombo.SelectedItem.ToString()), Int32.Parse(ColCountCombo.SelectedItem.ToString()));
		}

		private void ClearBtn_Click(object sender, EventArgs e)
		{
			ClearTiles();
		}
	}
}

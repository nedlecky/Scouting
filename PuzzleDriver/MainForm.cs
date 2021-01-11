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
		protected override void OnFormClosing(FormClosingEventArgs e)
		{
			if (e.CloseReason == CloseReason.UserClosing)
			{
				if (MessageBox.Show("Do you want to close the application?",
									"TilePuzzle Operation Confirmation",
									MessageBoxButtons.YesNo,
									MessageBoxIcon.Question) == DialogResult.No)
				{
					e.Cancel = true;
				}
			}
			if (e.Cancel == false)
				StopEnvironment();

			base.OnFormClosing(e);
		}
		private void ExitBtn_Click_1(object sender, EventArgs e)
		{
			this.Close();
		}

		private void MainForm_Load(object sender, EventArgs e)
		{
			Text = "PuzzleDriver 1.0";

			RowCountCombo.SelectedItem = "4";
			ColCountCombo.SelectedItem = "4";
			StartEnvironment();
			SetupBtn_Click(null, null);
		}

		private void StartEnvironment()
		{
			Log("StartEnvironment()");
			HeartbeatTmr.Interval = 1000;
			HeartbeatTmr.Enabled = true;
		}
		private void StopEnvironment()
		{
			Log("StopEnvironment()");
			HeartbeatTmr.Enabled = false;
		}

		TilePuzzle tilePuzzle;
		List<Button> tileButtonList = new List<Button>();
		private void CreateButtons(int nRows, int nCols)
		{
			int tileSize = 40;
			int startX = 220;
			int startY = 10;

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
			tilePuzzle = new TilePuzzle(this, nRows, nCols, tileButtonList);
		}

		private void ButtonHandler(object sender, EventArgs e)
		{
			int tileNum = 0;
			string label = ((Button)sender).Text;
			if (label != "")
				tileNum = Int32.Parse(label);
			Log("Button({0})", tileNum.ToString());
			bool fMoved = tilePuzzle.MoveTile(tileNum);
			if(fMoved)
			{
				tilePuzzle.LoadButtonsFromArray(tileButtonList);
			}
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

		private void RandomMoveBtn_Click(object sender, EventArgs e)
		{
			int n = 1;

			n = Int32.Parse(NumRandomMovesTxt.Text);
			tilePuzzle.MakeRandomMove(n);
			tilePuzzle.LoadButtonsFromArray(tileButtonList);
		}

		private void HeartbeatTmr_Tick(object sender, EventArgs e)
		{
			string now = DateTime.Now.ToString("s");
			TimeLbl.Text = now;
		}

		public void Log(string format, params object[] args)
		{
			string now = DateTime.Now.ToString("yyyy-MM-ddTHH:mm:ss.fff");
			CrawlerRTB.Text += now + ": " + String.Format(format, args) + "\n";
			CrawlerRTB.Select(CrawlerRTB.Text.Length - 1, 0);
			CrawlerRTB.ScrollToCaret();
		}

	}
}

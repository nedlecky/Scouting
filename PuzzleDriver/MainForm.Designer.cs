
namespace PuzzleDriver
{
	partial class MainForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.SetupBtn = new System.Windows.Forms.Button();
			this.ClearBtn = new System.Windows.Forms.Button();
			this.RowCountCombo = new System.Windows.Forms.ComboBox();
			this.ColCountCombo = new System.Windows.Forms.ComboBox();
			this.RandomMoveBtn = new System.Windows.Forms.Button();
			this.NumRandomMovesTxt = new System.Windows.Forms.TextBox();
			this.HeartbeatTmr = new System.Windows.Forms.Timer(this.components);
			this.ExitBtn = new System.Windows.Forms.Button();
			this.TimeLbl = new System.Windows.Forms.Label();
			this.CrawlerRTB = new System.Windows.Forms.RichTextBox();
			this.TryDeepSolveBtn = new System.Windows.Forms.Button();
			this.NumDeepSolvesTxt = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// SetupBtn
			// 
			this.SetupBtn.Location = new System.Drawing.Point(12, 12);
			this.SetupBtn.Name = "SetupBtn";
			this.SetupBtn.Size = new System.Drawing.Size(98, 21);
			this.SetupBtn.TabIndex = 0;
			this.SetupBtn.Text = "Setup";
			this.SetupBtn.UseVisualStyleBackColor = true;
			this.SetupBtn.Click += new System.EventHandler(this.SetupBtn_Click);
			// 
			// ClearBtn
			// 
			this.ClearBtn.Location = new System.Drawing.Point(12, 39);
			this.ClearBtn.Name = "ClearBtn";
			this.ClearBtn.Size = new System.Drawing.Size(98, 21);
			this.ClearBtn.TabIndex = 1;
			this.ClearBtn.Text = "Clear";
			this.ClearBtn.UseVisualStyleBackColor = true;
			this.ClearBtn.Click += new System.EventHandler(this.ClearBtn_Click);
			// 
			// RowCountCombo
			// 
			this.RowCountCombo.FormattingEnabled = true;
			this.RowCountCombo.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8"});
			this.RowCountCombo.Location = new System.Drawing.Point(123, 12);
			this.RowCountCombo.Name = "RowCountCombo";
			this.RowCountCombo.Size = new System.Drawing.Size(35, 21);
			this.RowCountCombo.TabIndex = 2;
			// 
			// ColCountCombo
			// 
			this.ColCountCombo.FormattingEnabled = true;
			this.ColCountCombo.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8"});
			this.ColCountCombo.Location = new System.Drawing.Point(169, 13);
			this.ColCountCombo.Name = "ColCountCombo";
			this.ColCountCombo.Size = new System.Drawing.Size(33, 21);
			this.ColCountCombo.TabIndex = 3;
			// 
			// RandomMoveBtn
			// 
			this.RandomMoveBtn.Location = new System.Drawing.Point(12, 72);
			this.RandomMoveBtn.Name = "RandomMoveBtn";
			this.RandomMoveBtn.Size = new System.Drawing.Size(98, 46);
			this.RandomMoveBtn.TabIndex = 4;
			this.RandomMoveBtn.Text = "Make N Random Moves";
			this.RandomMoveBtn.UseVisualStyleBackColor = true;
			this.RandomMoveBtn.Click += new System.EventHandler(this.RandomMoveBtn_Click);
			// 
			// NumRandomMovesTxt
			// 
			this.NumRandomMovesTxt.Location = new System.Drawing.Point(116, 72);
			this.NumRandomMovesTxt.Name = "NumRandomMovesTxt";
			this.NumRandomMovesTxt.Size = new System.Drawing.Size(86, 20);
			this.NumRandomMovesTxt.TabIndex = 5;
			this.NumRandomMovesTxt.Text = "1000000";
			// 
			// HeartbeatTmr
			// 
			this.HeartbeatTmr.Tick += new System.EventHandler(this.HeartbeatTmr_Tick);
			// 
			// ExitBtn
			// 
			this.ExitBtn.Location = new System.Drawing.Point(371, 559);
			this.ExitBtn.Name = "ExitBtn";
			this.ExitBtn.Size = new System.Drawing.Size(190, 28);
			this.ExitBtn.TabIndex = 6;
			this.ExitBtn.Text = "Exit";
			this.ExitBtn.UseVisualStyleBackColor = true;
			this.ExitBtn.Click += new System.EventHandler(this.ExitBtn_Click_1);
			// 
			// TimeLbl
			// 
			this.TimeLbl.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.TimeLbl.Location = new System.Drawing.Point(12, 564);
			this.TimeLbl.Name = "TimeLbl";
			this.TimeLbl.Size = new System.Drawing.Size(190, 26);
			this.TimeLbl.TabIndex = 7;
			this.TimeLbl.Text = "???";
			this.TimeLbl.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// CrawlerRTB
			// 
			this.CrawlerRTB.Location = new System.Drawing.Point(12, 407);
			this.CrawlerRTB.Name = "CrawlerRTB";
			this.CrawlerRTB.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.ForcedBoth;
			this.CrawlerRTB.Size = new System.Drawing.Size(549, 146);
			this.CrawlerRTB.TabIndex = 8;
			this.CrawlerRTB.Text = "";
			// 
			// TryDeepSolveBtn
			// 
			this.TryDeepSolveBtn.Location = new System.Drawing.Point(12, 124);
			this.TryDeepSolveBtn.Name = "TryDeepSolveBtn";
			this.TryDeepSolveBtn.Size = new System.Drawing.Size(98, 21);
			this.TryDeepSolveBtn.TabIndex = 9;
			this.TryDeepSolveBtn.Text = "Try Deep Solve";
			this.TryDeepSolveBtn.UseVisualStyleBackColor = true;
			this.TryDeepSolveBtn.Click += new System.EventHandler(this.TryDeepSolveBtn_Click);
			// 
			// NumDeepSolvesTxt
			// 
			this.NumDeepSolvesTxt.Location = new System.Drawing.Point(116, 125);
			this.NumDeepSolvesTxt.Name = "NumDeepSolvesTxt";
			this.NumDeepSolvesTxt.Size = new System.Drawing.Size(86, 20);
			this.NumDeepSolvesTxt.TabIndex = 10;
			this.NumDeepSolvesTxt.Text = "10";
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(573, 599);
			this.Controls.Add(this.NumDeepSolvesTxt);
			this.Controls.Add(this.TryDeepSolveBtn);
			this.Controls.Add(this.CrawlerRTB);
			this.Controls.Add(this.TimeLbl);
			this.Controls.Add(this.ExitBtn);
			this.Controls.Add(this.NumRandomMovesTxt);
			this.Controls.Add(this.RandomMoveBtn);
			this.Controls.Add(this.ColCountCombo);
			this.Controls.Add(this.RowCountCombo);
			this.Controls.Add(this.ClearBtn);
			this.Controls.Add(this.SetupBtn);
			this.MaximizeBox = false;
			this.Name = "MainForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Set in software";
			this.Load += new System.EventHandler(this.MainForm_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button SetupBtn;
		private System.Windows.Forms.Button ClearBtn;
		private System.Windows.Forms.ComboBox RowCountCombo;
		private System.Windows.Forms.ComboBox ColCountCombo;
		private System.Windows.Forms.Button RandomMoveBtn;
		private System.Windows.Forms.TextBox NumRandomMovesTxt;
		private System.Windows.Forms.Timer HeartbeatTmr;
		private System.Windows.Forms.Button ExitBtn;
		private System.Windows.Forms.Label TimeLbl;
		private System.Windows.Forms.RichTextBox CrawlerRTB;
		private System.Windows.Forms.Button TryDeepSolveBtn;
		private System.Windows.Forms.TextBox NumDeepSolvesTxt;
	}
}


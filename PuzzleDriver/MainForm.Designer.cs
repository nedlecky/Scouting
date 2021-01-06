
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
			this.SetupBtn = new System.Windows.Forms.Button();
			this.ClearBtn = new System.Windows.Forms.Button();
			this.RowCountCombo = new System.Windows.Forms.ComboBox();
			this.ColCountCombo = new System.Windows.Forms.ComboBox();
			this.SuspendLayout();
			// 
			// SetupBtn
			// 
			this.SetupBtn.Location = new System.Drawing.Point(12, 12);
			this.SetupBtn.Name = "SetupBtn";
			this.SetupBtn.Size = new System.Drawing.Size(98, 46);
			this.SetupBtn.TabIndex = 0;
			this.SetupBtn.Text = "Setup";
			this.SetupBtn.UseVisualStyleBackColor = true;
			this.SetupBtn.Click += new System.EventHandler(this.SetupBtn_Click);
			// 
			// ClearBtn
			// 
			this.ClearBtn.Location = new System.Drawing.Point(12, 64);
			this.ClearBtn.Name = "ClearBtn";
			this.ClearBtn.Size = new System.Drawing.Size(98, 46);
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
			this.RowCountCombo.Location = new System.Drawing.Point(131, 26);
			this.RowCountCombo.Name = "RowCountCombo";
			this.RowCountCombo.Size = new System.Drawing.Size(70, 21);
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
			this.ColCountCombo.Location = new System.Drawing.Point(207, 26);
			this.ColCountCombo.Name = "ColCountCombo";
			this.ColCountCombo.Size = new System.Drawing.Size(70, 21);
			this.ColCountCombo.TabIndex = 3;
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.ColCountCombo);
			this.Controls.Add(this.RowCountCombo);
			this.Controls.Add(this.ClearBtn);
			this.Controls.Add(this.SetupBtn);
			this.Name = "MainForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button SetupBtn;
		private System.Windows.Forms.Button ClearBtn;
		private System.Windows.Forms.ComboBox RowCountCombo;
		private System.Windows.Forms.ComboBox ColCountCombo;
	}
}


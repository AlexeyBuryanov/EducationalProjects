namespace Work_with_ListBox
{
    partial class FormMain
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.listBox2 = new System.Windows.Forms.ListBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonClearLB2 = new System.Windows.Forms.Button();
            this.buttonClearLB1 = new System.Windows.Forms.Button();
            this.buttonClearAll = new System.Windows.Forms.Button();
            this.buttonMoveToLB1 = new System.Windows.Forms.Button();
            this.buttonMoveToLB2 = new System.Windows.Forms.Button();
            this.buttonCopyToLB1 = new System.Windows.Forms.Button();
            this.buttonCopyToLB2 = new System.Windows.Forms.Button();
            this.buttonAddListBox2 = new System.Windows.Forms.Button();
            this.buttonAddListBox1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox = new System.Windows.Forms.MaskedTextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Items.AddRange(new object[] {
            "Лорем ипсум долор сит амет",
            "дицта делицатиссими ин",
            "нам харум саепе интеллегебат те",
            "граеце инструцтиор еос ан",
            "Вел ан видерер граецис фацилиси"});
            this.listBox1.Location = new System.Drawing.Point(24, 56);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(368, 290);
            this.listBox1.TabIndex = 9;
            this.listBox1.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // listBox2
            // 
            this.listBox2.FormattingEnabled = true;
            this.listBox2.Items.AddRange(new object[] {
            "Ад дицтас суавитате при",
            "Порро сцаевола вис ех",
            "ин хас граеце адверсариум",
            "Нец граеци луцилиус яуалисяуе",
            "яуис детрацто цотидиеяуе"});
            this.listBox2.Location = new System.Drawing.Point(888, 56);
            this.listBox2.Name = "listBox2";
            this.listBox2.Size = new System.Drawing.Size(368, 290);
            this.listBox2.TabIndex = 10;
            this.listBox2.SelectedIndexChanged += new System.EventHandler(this.listBox2_SelectedIndexChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Transparent;
            this.groupBox1.Controls.Add(this.buttonClearLB2);
            this.groupBox1.Controls.Add(this.buttonClearLB1);
            this.groupBox1.Controls.Add(this.buttonClearAll);
            this.groupBox1.Controls.Add(this.buttonMoveToLB1);
            this.groupBox1.Controls.Add(this.buttonMoveToLB2);
            this.groupBox1.Controls.Add(this.buttonCopyToLB1);
            this.groupBox1.Controls.Add(this.buttonCopyToLB2);
            this.groupBox1.Controls.Add(this.buttonAddListBox2);
            this.groupBox1.Controls.Add(this.buttonAddListBox1);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.textBox);
            this.groupBox1.Location = new System.Drawing.Point(424, 56);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(432, 288);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            // 
            // buttonClearLB2
            // 
            this.buttonClearLB2.BackColor = System.Drawing.SystemColors.Window;
            this.buttonClearLB2.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonClearLB2.FlatAppearance.BorderColor = System.Drawing.SystemColors.ControlLight;
            this.buttonClearLB2.FlatAppearance.MouseDownBackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.buttonClearLB2.FlatAppearance.MouseOverBackColor = System.Drawing.SystemColors.ActiveCaption;
            this.buttonClearLB2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonClearLB2.ForeColor = System.Drawing.SystemColors.WindowText;
            this.buttonClearLB2.Location = new System.Drawing.Point(240, 240);
            this.buttonClearLB2.Name = "buttonClearLB2";
            this.buttonClearLB2.Size = new System.Drawing.Size(163, 27);
            this.buttonClearLB2.TabIndex = 8;
            this.buttonClearLB2.Text = "Очистить лист-бокс &2";
            this.buttonClearLB2.UseVisualStyleBackColor = false;
            this.buttonClearLB2.Click += new System.EventHandler(this.buttonClearLB2_Click);
            // 
            // buttonClearLB1
            // 
            this.buttonClearLB1.BackColor = System.Drawing.SystemColors.Window;
            this.buttonClearLB1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonClearLB1.FlatAppearance.BorderColor = System.Drawing.SystemColors.ControlLight;
            this.buttonClearLB1.FlatAppearance.MouseDownBackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.buttonClearLB1.FlatAppearance.MouseOverBackColor = System.Drawing.SystemColors.ActiveCaption;
            this.buttonClearLB1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonClearLB1.ForeColor = System.Drawing.SystemColors.WindowText;
            this.buttonClearLB1.Location = new System.Drawing.Point(32, 240);
            this.buttonClearLB1.Name = "buttonClearLB1";
            this.buttonClearLB1.Size = new System.Drawing.Size(160, 27);
            this.buttonClearLB1.TabIndex = 7;
            this.buttonClearLB1.Text = "Очистить лист-бокс &1";
            this.buttonClearLB1.UseVisualStyleBackColor = false;
            this.buttonClearLB1.Click += new System.EventHandler(this.buttonClearLB1_Click);
            // 
            // buttonClearAll
            // 
            this.buttonClearAll.BackColor = System.Drawing.SystemColors.Window;
            this.buttonClearAll.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonClearAll.FlatAppearance.BorderColor = System.Drawing.SystemColors.ControlLight;
            this.buttonClearAll.FlatAppearance.MouseDownBackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.buttonClearAll.FlatAppearance.MouseOverBackColor = System.Drawing.SystemColors.ActiveCaption;
            this.buttonClearAll.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonClearAll.ForeColor = System.Drawing.SystemColors.WindowText;
            this.buttonClearAll.Location = new System.Drawing.Point(171, 80);
            this.buttonClearAll.Name = "buttonClearAll";
            this.buttonClearAll.Size = new System.Drawing.Size(92, 27);
            this.buttonClearAll.TabIndex = 13;
            this.buttonClearAll.Text = "Очистить вс&ё";
            this.buttonClearAll.UseVisualStyleBackColor = false;
            this.buttonClearAll.Click += new System.EventHandler(this.buttonClearAll_Click);
            // 
            // buttonMoveToLB1
            // 
            this.buttonMoveToLB1.BackColor = System.Drawing.SystemColors.Window;
            this.buttonMoveToLB1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonMoveToLB1.Enabled = false;
            this.buttonMoveToLB1.FlatAppearance.BorderColor = System.Drawing.SystemColors.ControlLight;
            this.buttonMoveToLB1.FlatAppearance.MouseDownBackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.buttonMoveToLB1.FlatAppearance.MouseOverBackColor = System.Drawing.SystemColors.ActiveCaption;
            this.buttonMoveToLB1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonMoveToLB1.ForeColor = System.Drawing.SystemColors.WindowText;
            this.buttonMoveToLB1.Location = new System.Drawing.Point(240, 188);
            this.buttonMoveToLB1.Name = "buttonMoveToLB1";
            this.buttonMoveToLB1.Size = new System.Drawing.Size(163, 27);
            this.buttonMoveToLB1.TabIndex = 6;
            this.buttonMoveToLB1.Text = "Пере&местить в лист-бокс 1";
            this.buttonMoveToLB1.UseVisualStyleBackColor = false;
            this.buttonMoveToLB1.Click += new System.EventHandler(this.buttonMoveToLB1_Click);
            // 
            // buttonMoveToLB2
            // 
            this.buttonMoveToLB2.BackColor = System.Drawing.SystemColors.Window;
            this.buttonMoveToLB2.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonMoveToLB2.Enabled = false;
            this.buttonMoveToLB2.FlatAppearance.BorderColor = System.Drawing.SystemColors.ControlLight;
            this.buttonMoveToLB2.FlatAppearance.MouseDownBackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.buttonMoveToLB2.FlatAppearance.MouseOverBackColor = System.Drawing.SystemColors.ActiveCaption;
            this.buttonMoveToLB2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonMoveToLB2.ForeColor = System.Drawing.SystemColors.WindowText;
            this.buttonMoveToLB2.Location = new System.Drawing.Point(32, 188);
            this.buttonMoveToLB2.Name = "buttonMoveToLB2";
            this.buttonMoveToLB2.Size = new System.Drawing.Size(160, 27);
            this.buttonMoveToLB2.TabIndex = 5;
            this.buttonMoveToLB2.Text = "Пе&реместить в лист-бокс 2";
            this.buttonMoveToLB2.UseVisualStyleBackColor = false;
            this.buttonMoveToLB2.Click += new System.EventHandler(this.buttonMoveToLB2_Click);
            // 
            // buttonCopyToLB1
            // 
            this.buttonCopyToLB1.BackColor = System.Drawing.SystemColors.Window;
            this.buttonCopyToLB1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonCopyToLB1.Enabled = false;
            this.buttonCopyToLB1.FlatAppearance.BorderColor = System.Drawing.SystemColors.ControlLight;
            this.buttonCopyToLB1.FlatAppearance.MouseDownBackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.buttonCopyToLB1.FlatAppearance.MouseOverBackColor = System.Drawing.SystemColors.ActiveCaption;
            this.buttonCopyToLB1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonCopyToLB1.ForeColor = System.Drawing.SystemColors.WindowText;
            this.buttonCopyToLB1.Location = new System.Drawing.Point(240, 136);
            this.buttonCopyToLB1.Name = "buttonCopyToLB1";
            this.buttonCopyToLB1.Size = new System.Drawing.Size(163, 27);
            this.buttonCopyToLB1.TabIndex = 4;
            this.buttonCopyToLB1.Text = "Ко&пировать в лист-бокс 1";
            this.buttonCopyToLB1.UseVisualStyleBackColor = false;
            this.buttonCopyToLB1.Click += new System.EventHandler(this.buttonCopyToLB1_Click);
            // 
            // buttonCopyToLB2
            // 
            this.buttonCopyToLB2.BackColor = System.Drawing.SystemColors.Window;
            this.buttonCopyToLB2.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonCopyToLB2.Enabled = false;
            this.buttonCopyToLB2.FlatAppearance.BorderColor = System.Drawing.SystemColors.ControlLight;
            this.buttonCopyToLB2.FlatAppearance.MouseDownBackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.buttonCopyToLB2.FlatAppearance.MouseOverBackColor = System.Drawing.SystemColors.ActiveCaption;
            this.buttonCopyToLB2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonCopyToLB2.ForeColor = System.Drawing.SystemColors.WindowText;
            this.buttonCopyToLB2.Location = new System.Drawing.Point(32, 136);
            this.buttonCopyToLB2.Name = "buttonCopyToLB2";
            this.buttonCopyToLB2.Size = new System.Drawing.Size(160, 27);
            this.buttonCopyToLB2.TabIndex = 3;
            this.buttonCopyToLB2.Text = "&Копировать в лист-бокс 2";
            this.buttonCopyToLB2.UseVisualStyleBackColor = false;
            this.buttonCopyToLB2.Click += new System.EventHandler(this.buttonCopyToLB2_Click);
            // 
            // buttonAddListBox2
            // 
            this.buttonAddListBox2.BackColor = System.Drawing.SystemColors.Window;
            this.buttonAddListBox2.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonAddListBox2.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonAddListBox2.FlatAppearance.BorderColor = System.Drawing.SystemColors.ControlLight;
            this.buttonAddListBox2.FlatAppearance.MouseDownBackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.buttonAddListBox2.FlatAppearance.MouseOverBackColor = System.Drawing.SystemColors.ActiveCaption;
            this.buttonAddListBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonAddListBox2.ForeColor = System.Drawing.SystemColors.WindowText;
            this.buttonAddListBox2.Location = new System.Drawing.Point(327, 80);
            this.buttonAddListBox2.Name = "buttonAddListBox2";
            this.buttonAddListBox2.Size = new System.Drawing.Size(75, 27);
            this.buttonAddListBox2.TabIndex = 2;
            this.buttonAddListBox2.Text = ">&>";
            this.buttonAddListBox2.UseVisualStyleBackColor = false;
            this.buttonAddListBox2.Click += new System.EventHandler(this.buttonAddListBox2_Click);
            // 
            // buttonAddListBox1
            // 
            this.buttonAddListBox1.BackColor = System.Drawing.SystemColors.Window;
            this.buttonAddListBox1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttonAddListBox1.FlatAppearance.BorderColor = System.Drawing.SystemColors.ControlLight;
            this.buttonAddListBox1.FlatAppearance.MouseDownBackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.buttonAddListBox1.FlatAppearance.MouseOverBackColor = System.Drawing.SystemColors.ActiveCaption;
            this.buttonAddListBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonAddListBox1.ForeColor = System.Drawing.SystemColors.WindowText;
            this.buttonAddListBox1.Location = new System.Drawing.Point(32, 80);
            this.buttonAddListBox1.Name = "buttonAddListBox1";
            this.buttonAddListBox1.Size = new System.Drawing.Size(75, 27);
            this.buttonAddListBox1.TabIndex = 1;
            this.buttonAddListBox1.Text = "&<<";
            this.buttonAddListBox1.UseVisualStyleBackColor = false;
            this.buttonAddListBox1.Click += new System.EventHandler(this.buttonAddListBox1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.SystemColors.HighlightText;
            this.label1.Location = new System.Drawing.Point(32, 32);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Строка:";
            // 
            // textBox
            // 
            this.textBox.Location = new System.Drawing.Point(32, 48);
            this.textBox.Name = "textBox";
            this.textBox.Size = new System.Drawing.Size(368, 20);
            this.textBox.TabIndex = 0;
            this.textBox.Text = "Это строка 1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.ForeColor = System.Drawing.SystemColors.HighlightText;
            this.label2.Location = new System.Drawing.Point(24, 24);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(146, 27);
            this.label2.TabIndex = 3;
            this.label2.Text = "Лист-бокс №1";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.Transparent;
            this.label3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.ForeColor = System.Drawing.SystemColors.HighlightText;
            this.label3.Location = new System.Drawing.Point(888, 24);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(146, 27);
            this.label3.TabIndex = 4;
            this.label3.Text = "Лист-бокс №2";
            // 
            // FormMain
            // 
            this.AcceptButton = this.buttonAddListBox1;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Desktop;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1284, 376);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.listBox2);
            this.Controls.Add(this.listBox1);
            this.ForeColor = System.Drawing.SystemColors.WindowText;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "FormMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Работа с лист-боксом";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.ListBox listBox2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button buttonClearLB2;
        private System.Windows.Forms.Button buttonClearLB1;
        private System.Windows.Forms.Button buttonClearAll;
        private System.Windows.Forms.Button buttonMoveToLB1;
        private System.Windows.Forms.Button buttonMoveToLB2;
        private System.Windows.Forms.Button buttonCopyToLB1;
        private System.Windows.Forms.Button buttonCopyToLB2;
        private System.Windows.Forms.Button buttonAddListBox2;
        private System.Windows.Forms.Button buttonAddListBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.MaskedTextBox textBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
    }
}


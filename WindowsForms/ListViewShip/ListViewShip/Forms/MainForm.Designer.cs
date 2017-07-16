namespace ListViewShip
{
    partial class MainForm
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
            if (disposing && (components != null)) {
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.mnuMain = new System.Windows.Forms.MenuStrip();
            this.mniFile = new System.Windows.Forms.ToolStripMenuItem();
            this.mniNew = new System.Windows.Forms.ToolStripMenuItem();
            this.mniOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.mniSave = new System.Windows.Forms.ToolStripMenuItem();
            this.mniSaveAs = new System.Windows.Forms.ToolStripMenuItem();
            this.mniSep1 = new System.Windows.Forms.ToolStripSeparator();
            this.mniExit = new System.Windows.Forms.ToolStripMenuItem();
            this.mniOperations = new System.Windows.Forms.ToolStripMenuItem();
            this.mniAdd = new System.Windows.Forms.ToolStripMenuItem();
            this.mniRemove = new System.Windows.Forms.ToolStripMenuItem();
            this.mniSep2 = new System.Windows.Forms.ToolStripSeparator();
            this.mniEdit = new System.Windows.Forms.ToolStripMenuItem();
            this.mniHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.mniAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.tstMain = new System.Windows.Forms.ToolStrip();
            this.tsbNew = new System.Windows.Forms.ToolStripButton();
            this.tsbOpen = new System.Windows.Forms.ToolStripButton();
            this.tsbSave = new System.Windows.Forms.ToolStripButton();
            this.tsbSep1 = new System.Windows.Forms.ToolStripSeparator();
            this.tsbAdd = new System.Windows.Forms.ToolStripButton();
            this.tsbRemove = new System.Windows.Forms.ToolStripButton();
            this.tsbEdit = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.tsbExit = new System.Windows.Forms.ToolStripButton();
            this.tsbAbout = new System.Windows.Forms.ToolStripButton();
            this.stsMain = new System.Windows.Forms.StatusStrip();
            this.statusBar = new System.Windows.Forms.ToolStripStatusLabel();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.lvShips = new System.Windows.Forms.ListView();
            this.chdId = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.chdName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.chdDisplacement = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.chdSpeed = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.chdCruisingRange = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.pbxShip = new System.Windows.Forms.PictureBox();
            this.ofdMain = new System.Windows.Forms.OpenFileDialog();
            this.sfdMain = new System.Windows.Forms.SaveFileDialog();
            this.sfdSaveAs = new System.Windows.Forms.SaveFileDialog();
            this.mnuMain.SuspendLayout();
            this.tstMain.SuspendLayout();
            this.stsMain.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbxShip)).BeginInit();
            this.SuspendLayout();
            // 
            // mnuMain
            // 
            this.mnuMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mniFile,
            this.mniOperations,
            this.mniHelp});
            this.mnuMain.Location = new System.Drawing.Point(0, 0);
            this.mnuMain.Name = "mnuMain";
            this.mnuMain.Size = new System.Drawing.Size(954, 24);
            this.mnuMain.TabIndex = 0;
            this.mnuMain.Text = "menuStrip1";
            this.mnuMain.MouseEnter += new System.EventHandler(this.otherControls_MouseEnter);
            // 
            // mniFile
            // 
            this.mniFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mniNew,
            this.mniOpen,
            this.mniSave,
            this.mniSaveAs,
            this.mniSep1,
            this.mniExit});
            this.mniFile.Name = "mniFile";
            this.mniFile.Size = new System.Drawing.Size(48, 20);
            this.mniFile.Tag = "0";
            this.mniFile.Text = "Файл";
            this.mniFile.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniNew
            // 
            this.mniNew.Image = global::ListViewShip.Properties.Resources.document;
            this.mniNew.Name = "mniNew";
            this.mniNew.Size = new System.Drawing.Size(162, 22);
            this.mniNew.Tag = "1";
            this.mniNew.Text = "Новый";
            this.mniNew.Click += new System.EventHandler(this.mniNew_Click);
            this.mniNew.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniOpen
            // 
            this.mniOpen.Image = global::ListViewShip.Properties.Resources.folder;
            this.mniOpen.Name = "mniOpen";
            this.mniOpen.Size = new System.Drawing.Size(162, 22);
            this.mniOpen.Tag = "2";
            this.mniOpen.Text = "Открыть...";
            this.mniOpen.Click += new System.EventHandler(this.mniOpen_Click);
            this.mniOpen.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniSave
            // 
            this.mniSave.Enabled = false;
            this.mniSave.Image = global::ListViewShip.Properties.Resources.memorycard;
            this.mniSave.Name = "mniSave";
            this.mniSave.Size = new System.Drawing.Size(162, 22);
            this.mniSave.Tag = "3";
            this.mniSave.Text = "Сохранить...";
            this.mniSave.Click += new System.EventHandler(this.mniSave_Click);
            this.mniSave.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniSaveAs
            // 
            this.mniSaveAs.Enabled = false;
            this.mniSaveAs.Name = "mniSaveAs";
            this.mniSaveAs.Size = new System.Drawing.Size(162, 22);
            this.mniSaveAs.Tag = "4";
            this.mniSaveAs.Text = "Сохранить как...";
            this.mniSaveAs.Click += new System.EventHandler(this.mniSaveAs_Click);
            this.mniSaveAs.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniSep1
            // 
            this.mniSep1.Name = "mniSep1";
            this.mniSep1.Size = new System.Drawing.Size(159, 6);
            // 
            // mniExit
            // 
            this.mniExit.Image = global::ListViewShip.Properties.Resources.power;
            this.mniExit.Name = "mniExit";
            this.mniExit.Size = new System.Drawing.Size(162, 22);
            this.mniExit.Tag = "5";
            this.mniExit.Text = "Выход";
            this.mniExit.Click += new System.EventHandler(this.mniExit_Click);
            this.mniExit.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniOperations
            // 
            this.mniOperations.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mniAdd,
            this.mniRemove,
            this.mniSep2,
            this.mniEdit});
            this.mniOperations.Name = "mniOperations";
            this.mniOperations.Size = new System.Drawing.Size(75, 20);
            this.mniOperations.Tag = "6";
            this.mniOperations.Text = "Операции";
            this.mniOperations.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniAdd
            // 
            this.mniAdd.Image = global::ListViewShip.Properties.Resources.cruise;
            this.mniAdd.Name = "mniAdd";
            this.mniAdd.Size = new System.Drawing.Size(256, 22);
            this.mniAdd.Tag = "7";
            this.mniAdd.Text = "Добавить данные о корабле...";
            this.mniAdd.Click += new System.EventHandler(this.mniAdd_Click);
            this.mniAdd.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniRemove
            // 
            this.mniRemove.Image = global::ListViewShip.Properties.Resources.x;
            this.mniRemove.Name = "mniRemove";
            this.mniRemove.Size = new System.Drawing.Size(256, 22);
            this.mniRemove.Tag = "8";
            this.mniRemove.Text = "Удалить корабль";
            this.mniRemove.Click += new System.EventHandler(this.mniRemove_Click);
            this.mniRemove.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniSep2
            // 
            this.mniSep2.Name = "mniSep2";
            this.mniSep2.Size = new System.Drawing.Size(253, 6);
            // 
            // mniEdit
            // 
            this.mniEdit.Image = global::ListViewShip.Properties.Resources.pencil;
            this.mniEdit.Name = "mniEdit";
            this.mniEdit.Size = new System.Drawing.Size(256, 22);
            this.mniEdit.Tag = "9";
            this.mniEdit.Text = "Редактировать данные корабля...";
            this.mniEdit.Click += new System.EventHandler(this.mniEdit_Click);
            this.mniEdit.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniHelp
            // 
            this.mniHelp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mniAbout});
            this.mniHelp.Name = "mniHelp";
            this.mniHelp.Size = new System.Drawing.Size(65, 20);
            this.mniHelp.Tag = "10";
            this.mniHelp.Text = "Справка";
            this.mniHelp.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniAbout
            // 
            this.mniAbout.Image = global::ListViewShip.Properties.Resources.dev;
            this.mniAbout.Name = "mniAbout";
            this.mniAbout.Size = new System.Drawing.Size(158, 22);
            this.mniAbout.Tag = "11";
            this.mniAbout.Text = "О программе...";
            this.mniAbout.Click += new System.EventHandler(this.mniAbout_Click);
            this.mniAbout.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // tstMain
            // 
            this.tstMain.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.tstMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbNew,
            this.tsbOpen,
            this.tsbSave,
            this.tsbSep1,
            this.tsbAdd,
            this.tsbRemove,
            this.tsbEdit,
            this.toolStripSeparator2,
            this.tsbExit,
            this.tsbAbout});
            this.tstMain.Location = new System.Drawing.Point(0, 24);
            this.tstMain.Name = "tstMain";
            this.tstMain.Size = new System.Drawing.Size(954, 31);
            this.tstMain.TabIndex = 1;
            this.tstMain.Text = "toolStrip1";
            this.tstMain.MouseEnter += new System.EventHandler(this.otherControls_MouseEnter);
            // 
            // tsbNew
            // 
            this.tsbNew.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbNew.Image = global::ListViewShip.Properties.Resources.document;
            this.tsbNew.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbNew.Name = "tsbNew";
            this.tsbNew.Size = new System.Drawing.Size(28, 28);
            this.tsbNew.Tag = "1";
            this.tsbNew.Text = "Новая коллекция";
            this.tsbNew.Click += new System.EventHandler(this.mniNew_Click);
            this.tsbNew.MouseEnter += new System.EventHandler(this.tsbNew_MouseEnter);
            // 
            // tsbOpen
            // 
            this.tsbOpen.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbOpen.Image = global::ListViewShip.Properties.Resources.folder;
            this.tsbOpen.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbOpen.Margin = new System.Windows.Forms.Padding(5, 1, 0, 2);
            this.tsbOpen.Name = "tsbOpen";
            this.tsbOpen.Size = new System.Drawing.Size(28, 28);
            this.tsbOpen.Tag = "2";
            this.tsbOpen.Text = "Загрузить коллекцию из файла";
            this.tsbOpen.Click += new System.EventHandler(this.mniOpen_Click);
            this.tsbOpen.MouseEnter += new System.EventHandler(this.tsbNew_MouseEnter);
            // 
            // tsbSave
            // 
            this.tsbSave.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbSave.Image = global::ListViewShip.Properties.Resources.memorycard;
            this.tsbSave.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbSave.Margin = new System.Windows.Forms.Padding(5, 1, 0, 2);
            this.tsbSave.Name = "tsbSave";
            this.tsbSave.Size = new System.Drawing.Size(28, 28);
            this.tsbSave.Tag = "3";
            this.tsbSave.Text = "Сохранить коллекцию в файл";
            this.tsbSave.Click += new System.EventHandler(this.mniSave_Click);
            this.tsbSave.MouseEnter += new System.EventHandler(this.tsbNew_MouseEnter);
            // 
            // tsbSep1
            // 
            this.tsbSep1.Name = "tsbSep1";
            this.tsbSep1.Size = new System.Drawing.Size(6, 31);
            // 
            // tsbAdd
            // 
            this.tsbAdd.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbAdd.Image = global::ListViewShip.Properties.Resources.cruise;
            this.tsbAdd.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbAdd.Margin = new System.Windows.Forms.Padding(5, 1, 0, 2);
            this.tsbAdd.Name = "tsbAdd";
            this.tsbAdd.Size = new System.Drawing.Size(28, 28);
            this.tsbAdd.Tag = "7";
            this.tsbAdd.Text = "Добавить корабль в коллекцию";
            this.tsbAdd.Click += new System.EventHandler(this.mniAdd_Click);
            this.tsbAdd.MouseEnter += new System.EventHandler(this.tsbNew_MouseEnter);
            // 
            // tsbRemove
            // 
            this.tsbRemove.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbRemove.Image = global::ListViewShip.Properties.Resources.x;
            this.tsbRemove.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbRemove.Margin = new System.Windows.Forms.Padding(5, 1, 0, 2);
            this.tsbRemove.Name = "tsbRemove";
            this.tsbRemove.Size = new System.Drawing.Size(28, 28);
            this.tsbRemove.Tag = "8";
            this.tsbRemove.Text = "Удалить корабль из коллекции ";
            this.tsbRemove.Click += new System.EventHandler(this.mniRemove_Click);
            this.tsbRemove.MouseEnter += new System.EventHandler(this.tsbNew_MouseEnter);
            // 
            // tsbEdit
            // 
            this.tsbEdit.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbEdit.Image = global::ListViewShip.Properties.Resources.pencil;
            this.tsbEdit.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbEdit.Margin = new System.Windows.Forms.Padding(5, 1, 0, 2);
            this.tsbEdit.Name = "tsbEdit";
            this.tsbEdit.Size = new System.Drawing.Size(28, 28);
            this.tsbEdit.Tag = "9";
            this.tsbEdit.Text = "Редактировать данные корабля в коллекции";
            this.tsbEdit.Click += new System.EventHandler(this.mniEdit_Click);
            this.tsbEdit.MouseEnter += new System.EventHandler(this.tsbNew_MouseEnter);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 31);
            // 
            // tsbExit
            // 
            this.tsbExit.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.tsbExit.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbExit.Image = global::ListViewShip.Properties.Resources.power;
            this.tsbExit.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbExit.Name = "tsbExit";
            this.tsbExit.Size = new System.Drawing.Size(28, 28);
            this.tsbExit.Tag = "5";
            this.tsbExit.Text = "Выход, завершение работы приложения";
            this.tsbExit.Click += new System.EventHandler(this.mniExit_Click);
            this.tsbExit.MouseEnter += new System.EventHandler(this.tsbNew_MouseEnter);
            // 
            // tsbAbout
            // 
            this.tsbAbout.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbAbout.Image = global::ListViewShip.Properties.Resources.dev;
            this.tsbAbout.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbAbout.Margin = new System.Windows.Forms.Padding(5, 1, 0, 2);
            this.tsbAbout.Name = "tsbAbout";
            this.tsbAbout.Size = new System.Drawing.Size(28, 28);
            this.tsbAbout.Tag = "11";
            this.tsbAbout.Text = "О программе";
            this.tsbAbout.Click += new System.EventHandler(this.mniAbout_Click);
            this.tsbAbout.MouseEnter += new System.EventHandler(this.tsbNew_MouseEnter);
            // 
            // stsMain
            // 
            this.stsMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusBar});
            this.stsMain.Location = new System.Drawing.Point(0, 359);
            this.stsMain.Name = "stsMain";
            this.stsMain.Size = new System.Drawing.Size(954, 22);
            this.stsMain.TabIndex = 2;
            this.stsMain.Text = "statusStrip1";
            this.stsMain.MouseEnter += new System.EventHandler(this.otherControls_MouseEnter);
            // 
            // statusBar
            // 
            this.statusBar.Name = "statusBar";
            this.statusBar.Size = new System.Drawing.Size(45, 17);
            this.statusBar.Text = "Готово";
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.Location = new System.Drawing.Point(0, 55);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.lvShips);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.pbxShip);
            this.splitContainer1.Size = new System.Drawing.Size(954, 304);
            this.splitContainer1.SplitterDistance = 507;
            this.splitContainer1.TabIndex = 3;
            // 
            // lvShips
            // 
            this.lvShips.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.chdId,
            this.chdName,
            this.chdDisplacement,
            this.chdSpeed,
            this.chdCruisingRange});
            this.lvShips.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lvShips.FullRowSelect = true;
            this.lvShips.GridLines = true;
            this.lvShips.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.lvShips.Location = new System.Drawing.Point(0, 0);
            this.lvShips.MultiSelect = false;
            this.lvShips.Name = "lvShips";
            this.lvShips.Size = new System.Drawing.Size(507, 304);
            this.lvShips.TabIndex = 0;
            this.lvShips.UseCompatibleStateImageBehavior = false;
            this.lvShips.View = System.Windows.Forms.View.Details;
            this.lvShips.SelectedIndexChanged += new System.EventHandler(this.lvShips_SelectedIndexChanged);
            this.lvShips.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.lvShips_MouseDoubleClick);
            this.lvShips.MouseEnter += new System.EventHandler(this.otherControls_MouseEnter);
            // 
            // chdId
            // 
            this.chdId.Text = "ИД";
            this.chdId.Width = 42;
            // 
            // chdName
            // 
            this.chdName.Text = "Название корабля";
            this.chdName.Width = 140;
            // 
            // chdDisplacement
            // 
            this.chdDisplacement.Text = "Водоизмещение";
            this.chdDisplacement.Width = 100;
            // 
            // chdSpeed
            // 
            this.chdSpeed.Text = "Скорость (узлов)";
            this.chdSpeed.Width = 100;
            // 
            // chdCruisingRange
            // 
            this.chdCruisingRange.Text = "Дальность плавания";
            this.chdCruisingRange.Width = 120;
            // 
            // pbxShip
            // 
            this.pbxShip.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pbxShip.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pbxShip.Location = new System.Drawing.Point(0, 0);
            this.pbxShip.Name = "pbxShip";
            this.pbxShip.Size = new System.Drawing.Size(443, 304);
            this.pbxShip.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pbxShip.TabIndex = 0;
            this.pbxShip.TabStop = false;
            this.pbxShip.MouseEnter += new System.EventHandler(this.otherControls_MouseEnter);
            // 
            // ofdMain
            // 
            this.ofdMain.Filter = "Файл данных о кораблях (*.ship)|*.ship|Все файлы (*.*)|*.*";
            // 
            // sfdMain
            // 
            this.sfdMain.Filter = "Файл данных о кораблях (*.ship)|*.ship|Все файлы (*.*)|*.*";
            this.sfdMain.Title = "Сохранить";
            // 
            // sfdSaveAs
            // 
            this.sfdSaveAs.Filter = "Файл данных о кораблях (*.ship)|*.ship|Все файлы (*.*)|*.*";
            this.sfdSaveAs.InitialDirectory = "d:\\";
            this.sfdSaveAs.Title = "Сохранить как";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(954, 381);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.stsMain);
            this.Controls.Add(this.tstMain);
            this.Controls.Add(this.mnuMain);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.mnuMain;
            this.MinimumSize = new System.Drawing.Size(940, 420);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Коллекция кораблей";
            this.mnuMain.ResumeLayout(false);
            this.mnuMain.PerformLayout();
            this.tstMain.ResumeLayout(false);
            this.tstMain.PerformLayout();
            this.stsMain.ResumeLayout(false);
            this.stsMain.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pbxShip)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip mnuMain;
        private System.Windows.Forms.ToolStrip tstMain;
        private System.Windows.Forms.StatusStrip stsMain;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.ListView lvShips;
        private System.Windows.Forms.PictureBox pbxShip;
        private System.Windows.Forms.ToolStripMenuItem mniFile;
        private System.Windows.Forms.ToolStripMenuItem mniNew;
        private System.Windows.Forms.ToolStripMenuItem mniOpen;
        private System.Windows.Forms.ToolStripMenuItem mniSave;
        private System.Windows.Forms.ToolStripSeparator mniSep1;
        private System.Windows.Forms.ToolStripMenuItem mniExit;
        private System.Windows.Forms.ToolStripMenuItem mniOperations;
        private System.Windows.Forms.ToolStripMenuItem mniAdd;
        private System.Windows.Forms.ToolStripMenuItem mniRemove;
        private System.Windows.Forms.ToolStripSeparator mniSep2;
        private System.Windows.Forms.ToolStripMenuItem mniEdit;
        private System.Windows.Forms.ToolStripMenuItem mniHelp;
        private System.Windows.Forms.ToolStripMenuItem mniAbout;
        private System.Windows.Forms.ToolStripButton tsbNew;
        private System.Windows.Forms.ToolStripButton tsbOpen;
        private System.Windows.Forms.ToolStripButton tsbSave;
        private System.Windows.Forms.ToolStripSeparator tsbSep1;
        private System.Windows.Forms.ToolStripButton tsbAdd;
        private System.Windows.Forms.ToolStripButton tsbRemove;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton tsbExit;
        private System.Windows.Forms.ToolStripStatusLabel statusBar;
        private System.Windows.Forms.ColumnHeader chdId;
        private System.Windows.Forms.ColumnHeader chdName;
        private System.Windows.Forms.ColumnHeader chdDisplacement;
        private System.Windows.Forms.ColumnHeader chdSpeed;
        private System.Windows.Forms.ColumnHeader chdCruisingRange;
        private System.Windows.Forms.ToolStripButton tsbEdit;
        private System.Windows.Forms.ToolStripButton tsbAbout;
        private System.Windows.Forms.OpenFileDialog ofdMain;
        private System.Windows.Forms.SaveFileDialog sfdMain;
        private System.Windows.Forms.ToolStripMenuItem mniSaveAs;
        private System.Windows.Forms.SaveFileDialog sfdSaveAs;
    }
}


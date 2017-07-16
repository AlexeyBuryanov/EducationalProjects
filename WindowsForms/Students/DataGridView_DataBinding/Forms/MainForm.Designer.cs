namespace DataGridView_DataBinding
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle6 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.dgvMain = new System.Windows.Forms.DataGridView();
            this.dgcId = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dgcSurname = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dgcGender = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.dgcBirthDate = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dgcCourse = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.dgcGroup = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.dgcScholarship = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.dgcAvgLevel = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.bnsDataGrid = new System.Windows.Forms.BindingSource(this.components);
            this.mnuMain = new System.Windows.Forms.MenuStrip();
            this.mniFile = new System.Windows.Forms.ToolStripMenuItem();
            this.mniNew = new System.Windows.Forms.ToolStripMenuItem();
            this.mniLoad = new System.Windows.Forms.ToolStripMenuItem();
            this.mniSave = new System.Windows.Forms.ToolStripMenuItem();
            this.mniSep1 = new System.Windows.Forms.ToolStripSeparator();
            this.mniExit = new System.Windows.Forms.ToolStripMenuItem();
            this.справкаToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.оПрограммеToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mniData = new System.Windows.Forms.ToolStripMenuItem();
            this.mniSort = new System.Windows.Forms.ToolStripMenuItem();
            this.mniSurname = new System.Windows.Forms.ToolStripMenuItem();
            this.mniAvgLevel = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.statusBar = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusBar2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStrip = new System.Windows.Forms.ToolStrip();
            this.tsbNew = new System.Windows.Forms.ToolStripButton();
            this.tsbLoad = new System.Windows.Forms.ToolStripButton();
            this.tsbSave = new System.Windows.Forms.ToolStripButton();
            this.tsbExit = new System.Windows.Forms.ToolStripButton();
            this.sfdStudents = new System.Windows.Forms.SaveFileDialog();
            this.ofdStudents = new System.Windows.Forms.OpenFileDialog();
            this.bnvMain = new System.Windows.Forms.BindingNavigator(this.components);
            this.bindingNavigatorAddNewItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorCountItem = new System.Windows.Forms.ToolStripLabel();
            this.bindingNavigatorDeleteItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorMoveFirstItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorMovePreviousItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.bindingNavigatorPositionItem = new System.Windows.Forms.ToolStripTextBox();
            this.bindingNavigatorSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.bindingNavigatorMoveNextItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorMoveLastItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.tbcData = new System.Windows.Forms.TabControl();
            this.tpgStudents = new System.Windows.Forms.TabPage();
            this.tpgMarks = new System.Windows.Forms.TabPage();
            this.dgvMarks = new System.Windows.Forms.DataGridView();
            this.dgcSubject = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.dgcLevel = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.bnsMarks = new System.Windows.Forms.BindingSource(this.components);
            this.lblSurname = new System.Windows.Forms.Label();
            this.studentBindingSource = new System.Windows.Forms.BindingSource(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.dgvMain)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bnsDataGrid)).BeginInit();
            this.mnuMain.SuspendLayout();
            this.statusStrip.SuspendLayout();
            this.toolStrip.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bnvMain)).BeginInit();
            this.bnvMain.SuspendLayout();
            this.tbcData.SuspendLayout();
            this.tpgStudents.SuspendLayout();
            this.tpgMarks.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvMarks)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bnsMarks)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.studentBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // dgvMain
            // 
            this.dgvMain.AllowUserToResizeColumns = false;
            this.dgvMain.AllowUserToResizeRows = false;
            this.dgvMain.AutoGenerateColumns = false;
            this.dgvMain.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dgvMain.CellBorderStyle = System.Windows.Forms.DataGridViewCellBorderStyle.Raised;
            this.dgvMain.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvMain.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dgcId,
            this.dgcSurname,
            this.dgcGender,
            this.dgcBirthDate,
            this.dgcCourse,
            this.dgcGroup,
            this.dgcScholarship,
            this.dgcAvgLevel});
            this.dgvMain.DataSource = this.bnsDataGrid;
            this.dgvMain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgvMain.Location = new System.Drawing.Point(3, 3);
            this.dgvMain.Name = "dgvMain";
            this.dgvMain.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.dgvMain.Size = new System.Drawing.Size(1070, 301);
            this.dgvMain.TabIndex = 0;
            this.dgvMain.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.dgvMain_CellFormatting);
            this.dgvMain.CellValidating += new System.Windows.Forms.DataGridViewCellValidatingEventHandler(this.dgvMain_CellValidating);
            this.dgvMain.CurrentCellDirtyStateChanged += new System.EventHandler(this.dgvMain_CurrentCellDirtyStateChanged);
            this.dgvMain.RowValidating += new System.Windows.Forms.DataGridViewCellCancelEventHandler(this.dgvMain_RowValidating);
            // 
            // dgcId
            // 
            this.dgcId.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dgcId.DataPropertyName = "Id";
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.GrayText;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.GrayText;
            this.dgcId.DefaultCellStyle = dataGridViewCellStyle1;
            this.dgcId.DividerWidth = 1;
            this.dgcId.FillWeight = 50F;
            this.dgcId.HeaderText = "Номер";
            this.dgcId.Name = "dgcId";
            this.dgcId.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.dgcId.ToolTipText = "Идентификатор студента";
            // 
            // dgcSurname
            // 
            this.dgcSurname.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dgcSurname.DataPropertyName = "Surname";
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            this.dgcSurname.DefaultCellStyle = dataGridViewCellStyle2;
            this.dgcSurname.DividerWidth = 1;
            this.dgcSurname.FillWeight = 138.85F;
            this.dgcSurname.HeaderText = "Фамилия И.О.";
            this.dgcSurname.Name = "dgcSurname";
            this.dgcSurname.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.dgcSurname.ToolTipText = "Фамилия, имя, отчество";
            // 
            // dgcGender
            // 
            this.dgcGender.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dgcGender.DataPropertyName = "Gender";
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.dgcGender.DefaultCellStyle = dataGridViewCellStyle3;
            this.dgcGender.DividerWidth = 1;
            this.dgcGender.FillWeight = 37.02666F;
            this.dgcGender.HeaderText = "Пол";
            this.dgcGender.Items.AddRange(new object[] {
            "М",
            "Ж"});
            this.dgcGender.Name = "dgcGender";
            this.dgcGender.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.dgcGender.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.dgcGender.ToolTipText = "Гендер";
            // 
            // dgcBirthDate
            // 
            this.dgcBirthDate.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dgcBirthDate.DataPropertyName = "BirthDate";
            dataGridViewCellStyle4.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            this.dgcBirthDate.DefaultCellStyle = dataGridViewCellStyle4;
            this.dgcBirthDate.DividerWidth = 1;
            this.dgcBirthDate.FillWeight = 80F;
            this.dgcBirthDate.HeaderText = "Дата рождения";
            this.dgcBirthDate.Name = "dgcBirthDate";
            this.dgcBirthDate.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.dgcBirthDate.ToolTipText = "Дата рождения";
            // 
            // dgcCourse
            // 
            this.dgcCourse.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dgcCourse.DataPropertyName = "Course";
            dataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.dgcCourse.DefaultCellStyle = dataGridViewCellStyle5;
            this.dgcCourse.DividerWidth = 1;
            this.dgcCourse.FillWeight = 32.39833F;
            this.dgcCourse.HeaderText = "Курс";
            this.dgcCourse.Name = "dgcCourse";
            this.dgcCourse.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.dgcCourse.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.dgcCourse.ToolTipText = "Курс";
            // 
            // dgcGroup
            // 
            this.dgcGroup.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dgcGroup.DataPropertyName = "Group";
            dataGridViewCellStyle6.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            this.dgcGroup.DefaultCellStyle = dataGridViewCellStyle6;
            this.dgcGroup.DividerWidth = 1;
            this.dgcGroup.FillWeight = 64.79666F;
            this.dgcGroup.HeaderText = "Группа";
            this.dgcGroup.Items.AddRange(new object[] {
            "ПСУ 1-27",
            "ПСД 1-29",
            "ПСУ 1-31",
            "ПСД 1-31",
            "ЕКО 15-П91",
            "ЕКО 14-П81",
            "ЕКО 15-Д91",
            "ЕКО 15-А91",
            "ЕКО 14-Д81",
            "ЕКО 14-А81",
            ""});
            this.dgcGroup.Name = "dgcGroup";
            this.dgcGroup.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.dgcGroup.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.dgcGroup.ToolTipText = "Группа";
            // 
            // dgcScholarship
            // 
            this.dgcScholarship.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dgcScholarship.DataPropertyName = "Scholarship";
            this.dgcScholarship.DividerWidth = 1;
            this.dgcScholarship.FillWeight = 55.54F;
            this.dgcScholarship.HeaderText = "Стипендия";
            this.dgcScholarship.Name = "dgcScholarship";
            this.dgcScholarship.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.dgcScholarship.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.dgcScholarship.ToolTipText = "Есть ли стипендия";
            // 
            // dgcAvgLevel
            // 
            this.dgcAvgLevel.FillWeight = 65F;
            this.dgcAvgLevel.HeaderText = "Средний балл";
            this.dgcAvgLevel.Name = "dgcAvgLevel";
            this.dgcAvgLevel.ReadOnly = true;
            // 
            // bnsDataGrid
            // 
            this.bnsDataGrid.DataSource = typeof(DataGridView_DataBinding.Student);
            // 
            // mnuMain
            // 
            this.mnuMain.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.mnuMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mniFile,
            this.справкаToolStripMenuItem,
            this.mniData});
            this.mnuMain.Location = new System.Drawing.Point(0, 0);
            this.mnuMain.Name = "mnuMain";
            this.mnuMain.Size = new System.Drawing.Size(1084, 24);
            this.mnuMain.TabIndex = 1;
            this.mnuMain.Text = "menuStrip1";
            this.mnuMain.MouseEnter += new System.EventHandler(this.otherControls_MouseEnter);
            // 
            // mniFile
            // 
            this.mniFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mniNew,
            this.mniLoad,
            this.mniSave,
            this.mniSep1,
            this.mniExit});
            this.mniFile.Name = "mniFile";
            this.mniFile.Size = new System.Drawing.Size(48, 20);
            this.mniFile.Tag = "0";
            this.mniFile.Text = "&Файл";
            this.mniFile.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniNew
            // 
            this.mniNew.Image = ((System.Drawing.Image)(resources.GetObject("mniNew.Image")));
            this.mniNew.Name = "mniNew";
            this.mniNew.Size = new System.Drawing.Size(141, 22);
            this.mniNew.Tag = "1";
            this.mniNew.Text = "&Новый";
            this.mniNew.Click += new System.EventHandler(this.new_Click);
            this.mniNew.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniLoad
            // 
            this.mniLoad.Image = ((System.Drawing.Image)(resources.GetObject("mniLoad.Image")));
            this.mniLoad.Name = "mniLoad";
            this.mniLoad.Size = new System.Drawing.Size(141, 22);
            this.mniLoad.Tag = "2";
            this.mniLoad.Text = "&Загрузить...";
            this.mniLoad.Click += new System.EventHandler(this.mniLoad_Click);
            this.mniLoad.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniSave
            // 
            this.mniSave.Image = ((System.Drawing.Image)(resources.GetObject("mniSave.Image")));
            this.mniSave.Name = "mniSave";
            this.mniSave.Size = new System.Drawing.Size(141, 22);
            this.mniSave.Tag = "3";
            this.mniSave.Text = "&Сохранить...";
            this.mniSave.Click += new System.EventHandler(this.mniSave_Click);
            this.mniSave.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniSep1
            // 
            this.mniSep1.Name = "mniSep1";
            this.mniSep1.Size = new System.Drawing.Size(138, 6);
            // 
            // mniExit
            // 
            this.mniExit.Image = ((System.Drawing.Image)(resources.GetObject("mniExit.Image")));
            this.mniExit.Name = "mniExit";
            this.mniExit.Size = new System.Drawing.Size(141, 22);
            this.mniExit.Tag = "4";
            this.mniExit.Text = "Вы&ход";
            this.mniExit.Click += new System.EventHandler(this.mniExit_Click);
            this.mniExit.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // справкаToolStripMenuItem
            // 
            this.справкаToolStripMenuItem.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.справкаToolStripMenuItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.справкаToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.оПрограммеToolStripMenuItem});
            this.справкаToolStripMenuItem.Name = "справкаToolStripMenuItem";
            this.справкаToolStripMenuItem.Size = new System.Drawing.Size(65, 20);
            this.справкаToolStripMenuItem.Tag = "5";
            this.справкаToolStripMenuItem.Text = "Справ&ка";
            this.справкаToolStripMenuItem.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // оПрограммеToolStripMenuItem
            // 
            this.оПрограммеToolStripMenuItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.оПрограммеToolStripMenuItem.Name = "оПрограммеToolStripMenuItem";
            this.оПрограммеToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.оПрограммеToolStripMenuItem.Tag = "6";
            this.оПрограммеToolStripMenuItem.Text = "О программе";
            this.оПрограммеToolStripMenuItem.Click += new System.EventHandler(this.mniAbout_Click);
            this.оПрограммеToolStripMenuItem.MouseEnter += new System.EventHandler(this.menuItem_MouseEnter);
            // 
            // mniData
            // 
            this.mniData.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mniSort});
            this.mniData.Name = "mniData";
            this.mniData.Size = new System.Drawing.Size(62, 20);
            this.mniData.Text = "Данные";
            // 
            // mniSort
            // 
            this.mniSort.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mniSurname,
            this.mniAvgLevel});
            this.mniSort.Name = "mniSort";
            this.mniSort.Size = new System.Drawing.Size(152, 22);
            this.mniSort.Text = "Сортировка";
            // 
            // mniSurname
            // 
            this.mniSurname.Name = "mniSurname";
            this.mniSurname.Size = new System.Drawing.Size(182, 22);
            this.mniSurname.Tag = "1";
            this.mniSurname.Text = "По фамилии";
            this.mniSurname.Click += new System.EventHandler(this.mniAnySort_Click);
            // 
            // mniAvgLevel
            // 
            this.mniAvgLevel.Name = "mniAvgLevel";
            this.mniAvgLevel.Size = new System.Drawing.Size(182, 22);
            this.mniAvgLevel.Tag = "2";
            this.mniAvgLevel.Text = "По среднему баллу";
            this.mniAvgLevel.Click += new System.EventHandler(this.mniAnySort_Click);
            // 
            // statusStrip
            // 
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusBar,
            this.statusBar2});
            this.statusStrip.Location = new System.Drawing.Point(0, 419);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(1084, 22);
            this.statusStrip.TabIndex = 2;
            this.statusStrip.Text = "statusStrip";
            this.statusStrip.MouseEnter += new System.EventHandler(this.otherControls_MouseEnter);
            // 
            // statusBar
            // 
            this.statusBar.AutoSize = false;
            this.statusBar.Name = "statusBar";
            this.statusBar.Size = new System.Drawing.Size(400, 17);
            this.statusBar.Text = "Готово";
            this.statusBar.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // statusBar2
            // 
            this.statusBar2.Name = "statusBar2";
            this.statusBar2.Size = new System.Drawing.Size(669, 17);
            this.statusBar2.Spring = true;
            this.statusBar2.TextDirection = System.Windows.Forms.ToolStripTextDirection.Horizontal;
            // 
            // toolStrip
            // 
            this.toolStrip.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.toolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbNew,
            this.tsbLoad,
            this.tsbSave,
            this.tsbExit});
            this.toolStrip.Location = new System.Drawing.Point(0, 24);
            this.toolStrip.Name = "toolStrip";
            this.toolStrip.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.toolStrip.Size = new System.Drawing.Size(1084, 31);
            this.toolStrip.TabIndex = 3;
            this.toolStrip.MouseEnter += new System.EventHandler(this.otherControls_MouseEnter);
            // 
            // tsbNew
            // 
            this.tsbNew.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbNew.Image = ((System.Drawing.Image)(resources.GetObject("tsbNew.Image")));
            this.tsbNew.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbNew.Margin = new System.Windows.Forms.Padding(12, 1, 0, 2);
            this.tsbNew.Name = "tsbNew";
            this.tsbNew.Size = new System.Drawing.Size(28, 28);
            this.tsbNew.Tag = "1";
            this.tsbNew.Text = "Новый";
            this.tsbNew.Click += new System.EventHandler(this.new_Click);
            this.tsbNew.MouseEnter += new System.EventHandler(this.toolItem_MouseEnter);
            // 
            // tsbLoad
            // 
            this.tsbLoad.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbLoad.Image = ((System.Drawing.Image)(resources.GetObject("tsbLoad.Image")));
            this.tsbLoad.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbLoad.Margin = new System.Windows.Forms.Padding(5, 1, 0, 2);
            this.tsbLoad.Name = "tsbLoad";
            this.tsbLoad.Size = new System.Drawing.Size(28, 28);
            this.tsbLoad.Tag = "2";
            this.tsbLoad.Text = "Загрузить...";
            this.tsbLoad.Click += new System.EventHandler(this.mniLoad_Click);
            this.tsbLoad.MouseEnter += new System.EventHandler(this.toolItem_MouseEnter);
            // 
            // tsbSave
            // 
            this.tsbSave.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbSave.Image = ((System.Drawing.Image)(resources.GetObject("tsbSave.Image")));
            this.tsbSave.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbSave.Margin = new System.Windows.Forms.Padding(5, 1, 0, 2);
            this.tsbSave.Name = "tsbSave";
            this.tsbSave.Size = new System.Drawing.Size(28, 28);
            this.tsbSave.Tag = "3";
            this.tsbSave.Text = "Сохранить...";
            this.tsbSave.Click += new System.EventHandler(this.mniSave_Click);
            this.tsbSave.MouseEnter += new System.EventHandler(this.toolItem_MouseEnter);
            // 
            // tsbExit
            // 
            this.tsbExit.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.tsbExit.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbExit.Image = ((System.Drawing.Image)(resources.GetObject("tsbExit.Image")));
            this.tsbExit.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbExit.Name = "tsbExit";
            this.tsbExit.Size = new System.Drawing.Size(28, 28);
            this.tsbExit.Tag = "4";
            this.tsbExit.Text = "Выход";
            this.tsbExit.Click += new System.EventHandler(this.mniExit_Click);
            this.tsbExit.MouseEnter += new System.EventHandler(this.toolItem_MouseEnter);
            // 
            // sfdStudents
            // 
            this.sfdStudents.Filter = "Данные студентов (*.students)|*.students|Все файлы (*.*)|*.*";
            // 
            // ofdStudents
            // 
            this.ofdStudents.Filter = "Данные студентов (*.students)|*.students|Все файлы (*.*)|*.*";
            // 
            // bnvMain
            // 
            this.bnvMain.AddNewItem = this.bindingNavigatorAddNewItem;
            this.bnvMain.BindingSource = this.bnsDataGrid;
            this.bnvMain.CountItem = this.bindingNavigatorCountItem;
            this.bnvMain.DeleteItem = this.bindingNavigatorDeleteItem;
            this.bnvMain.ImageScalingSize = new System.Drawing.Size(19, 19);
            this.bnvMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.bindingNavigatorMoveFirstItem,
            this.bindingNavigatorMovePreviousItem,
            this.bindingNavigatorSeparator,
            this.bindingNavigatorPositionItem,
            this.bindingNavigatorCountItem,
            this.bindingNavigatorSeparator1,
            this.bindingNavigatorMoveNextItem,
            this.bindingNavigatorMoveLastItem,
            this.bindingNavigatorSeparator2,
            this.bindingNavigatorAddNewItem,
            this.bindingNavigatorDeleteItem});
            this.bnvMain.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.Flow;
            this.bnvMain.Location = new System.Drawing.Point(0, 55);
            this.bnvMain.MoveFirstItem = this.bindingNavigatorMoveFirstItem;
            this.bnvMain.MoveLastItem = this.bindingNavigatorMoveLastItem;
            this.bnvMain.MoveNextItem = this.bindingNavigatorMoveNextItem;
            this.bnvMain.MovePreviousItem = this.bindingNavigatorMovePreviousItem;
            this.bnvMain.Name = "bnvMain";
            this.bnvMain.PositionItem = this.bindingNavigatorPositionItem;
            this.bnvMain.Size = new System.Drawing.Size(1084, 26);
            this.bnvMain.TabIndex = 4;
            this.bnvMain.Text = "bindingNavigator1";
            this.bnvMain.MouseEnter += new System.EventHandler(this.otherControls_MouseEnter);
            // 
            // bindingNavigatorAddNewItem
            // 
            this.bindingNavigatorAddNewItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorAddNewItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorAddNewItem.Image")));
            this.bindingNavigatorAddNewItem.Name = "bindingNavigatorAddNewItem";
            this.bindingNavigatorAddNewItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorAddNewItem.Size = new System.Drawing.Size(23, 23);
            this.bindingNavigatorAddNewItem.Text = "Добавить";
            // 
            // bindingNavigatorCountItem
            // 
            this.bindingNavigatorCountItem.Name = "bindingNavigatorCountItem";
            this.bindingNavigatorCountItem.Size = new System.Drawing.Size(43, 15);
            this.bindingNavigatorCountItem.Text = "для {0}";
            this.bindingNavigatorCountItem.ToolTipText = "Общее число элементов";
            // 
            // bindingNavigatorDeleteItem
            // 
            this.bindingNavigatorDeleteItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorDeleteItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorDeleteItem.Image")));
            this.bindingNavigatorDeleteItem.Name = "bindingNavigatorDeleteItem";
            this.bindingNavigatorDeleteItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorDeleteItem.Size = new System.Drawing.Size(23, 23);
            this.bindingNavigatorDeleteItem.Text = "Удалить";
            // 
            // bindingNavigatorMoveFirstItem
            // 
            this.bindingNavigatorMoveFirstItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMoveFirstItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveFirstItem.Image")));
            this.bindingNavigatorMoveFirstItem.Name = "bindingNavigatorMoveFirstItem";
            this.bindingNavigatorMoveFirstItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMoveFirstItem.Size = new System.Drawing.Size(23, 23);
            this.bindingNavigatorMoveFirstItem.Text = "Переместить в начало";
            // 
            // bindingNavigatorMovePreviousItem
            // 
            this.bindingNavigatorMovePreviousItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMovePreviousItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMovePreviousItem.Image")));
            this.bindingNavigatorMovePreviousItem.Name = "bindingNavigatorMovePreviousItem";
            this.bindingNavigatorMovePreviousItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMovePreviousItem.Size = new System.Drawing.Size(23, 23);
            this.bindingNavigatorMovePreviousItem.Text = "Переместить назад";
            // 
            // bindingNavigatorSeparator
            // 
            this.bindingNavigatorSeparator.Name = "bindingNavigatorSeparator";
            this.bindingNavigatorSeparator.Size = new System.Drawing.Size(6, 23);
            // 
            // bindingNavigatorPositionItem
            // 
            this.bindingNavigatorPositionItem.AccessibleName = "Положение";
            this.bindingNavigatorPositionItem.AutoSize = false;
            this.bindingNavigatorPositionItem.Name = "bindingNavigatorPositionItem";
            this.bindingNavigatorPositionItem.Size = new System.Drawing.Size(50, 23);
            this.bindingNavigatorPositionItem.Text = "0";
            this.bindingNavigatorPositionItem.ToolTipText = "Текущее положение";
            // 
            // bindingNavigatorSeparator1
            // 
            this.bindingNavigatorSeparator1.Name = "bindingNavigatorSeparator1";
            this.bindingNavigatorSeparator1.Size = new System.Drawing.Size(6, 23);
            // 
            // bindingNavigatorMoveNextItem
            // 
            this.bindingNavigatorMoveNextItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMoveNextItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveNextItem.Image")));
            this.bindingNavigatorMoveNextItem.Name = "bindingNavigatorMoveNextItem";
            this.bindingNavigatorMoveNextItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMoveNextItem.Size = new System.Drawing.Size(23, 23);
            this.bindingNavigatorMoveNextItem.Text = "Переместить вперед";
            // 
            // bindingNavigatorMoveLastItem
            // 
            this.bindingNavigatorMoveLastItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMoveLastItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveLastItem.Image")));
            this.bindingNavigatorMoveLastItem.Name = "bindingNavigatorMoveLastItem";
            this.bindingNavigatorMoveLastItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMoveLastItem.Size = new System.Drawing.Size(23, 23);
            this.bindingNavigatorMoveLastItem.Text = "Переместить в конец";
            // 
            // bindingNavigatorSeparator2
            // 
            this.bindingNavigatorSeparator2.Name = "bindingNavigatorSeparator2";
            this.bindingNavigatorSeparator2.Size = new System.Drawing.Size(6, 23);
            // 
            // tbcData
            // 
            this.tbcData.Controls.Add(this.tpgStudents);
            this.tbcData.Controls.Add(this.tpgMarks);
            this.tbcData.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tbcData.Font = new System.Drawing.Font("Trebuchet MS", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.tbcData.Location = new System.Drawing.Point(0, 81);
            this.tbcData.Name = "tbcData";
            this.tbcData.SelectedIndex = 0;
            this.tbcData.Size = new System.Drawing.Size(1084, 338);
            this.tbcData.TabIndex = 5;
            // 
            // tpgStudents
            // 
            this.tpgStudents.Controls.Add(this.dgvMain);
            this.tpgStudents.Location = new System.Drawing.Point(4, 27);
            this.tpgStudents.Name = "tpgStudents";
            this.tpgStudents.Padding = new System.Windows.Forms.Padding(3);
            this.tpgStudents.Size = new System.Drawing.Size(1076, 307);
            this.tpgStudents.TabIndex = 0;
            this.tpgStudents.Text = "Студенты";
            this.tpgStudents.UseVisualStyleBackColor = true;
            // 
            // tpgMarks
            // 
            this.tpgMarks.Controls.Add(this.dgvMarks);
            this.tpgMarks.Controls.Add(this.lblSurname);
            this.tpgMarks.Location = new System.Drawing.Point(4, 27);
            this.tpgMarks.Name = "tpgMarks";
            this.tpgMarks.Padding = new System.Windows.Forms.Padding(3);
            this.tpgMarks.Size = new System.Drawing.Size(1076, 307);
            this.tpgMarks.TabIndex = 1;
            this.tpgMarks.Text = "Оценки";
            this.tpgMarks.UseVisualStyleBackColor = true;
            // 
            // dgvMarks
            // 
            this.dgvMarks.AutoGenerateColumns = false;
            this.dgvMarks.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvMarks.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dgcSubject,
            this.dgcLevel});
            this.dgvMarks.DataSource = this.bnsMarks;
            this.dgvMarks.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgvMarks.Location = new System.Drawing.Point(3, 21);
            this.dgvMarks.Name = "dgvMarks";
            this.dgvMarks.Size = new System.Drawing.Size(1070, 283);
            this.dgvMarks.TabIndex = 0;
            // 
            // dgcSubject
            // 
            this.dgcSubject.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dgcSubject.DataPropertyName = "Subject";
            this.dgcSubject.FillWeight = 300F;
            this.dgcSubject.HeaderText = "Предмет";
            this.dgcSubject.Items.AddRange(new object[] {
            "Основы программирования",
            "Аппаратное обеспечение",
            "ООП C++",
            "WinAPI",
            "HTML_CSS",
            "JavaScript",
            "C#",
            "WindowsForms",
            "XML",
            "DT",
            "MS SQL Server"});
            this.dgcSubject.Name = "dgcSubject";
            this.dgcSubject.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.dgcSubject.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // dgcLevel
            // 
            this.dgcLevel.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dgcLevel.DataPropertyName = "Level";
            this.dgcLevel.HeaderText = "Оценка";
            this.dgcLevel.Name = "dgcLevel";
            this.dgcLevel.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.dgcLevel.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // lblSurname
            // 
            this.lblSurname.Dock = System.Windows.Forms.DockStyle.Top;
            this.lblSurname.Location = new System.Drawing.Point(3, 3);
            this.lblSurname.Name = "lblSurname";
            this.lblSurname.Size = new System.Drawing.Size(1070, 18);
            this.lblSurname.TabIndex = 1;
            this.lblSurname.Text = "Студент не выбран";
            this.lblSurname.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // studentBindingSource
            // 
            this.studentBindingSource.DataSource = typeof(DataGridView_DataBinding.Student);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1084, 441);
            this.Controls.Add(this.tbcData);
            this.Controls.Add(this.bnvMain);
            this.Controls.Add(this.toolStrip);
            this.Controls.Add(this.mnuMain);
            this.Controls.Add(this.statusStrip);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.mnuMain;
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Данные о студентах";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.dgvMain)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bnsDataGrid)).EndInit();
            this.mnuMain.ResumeLayout(false);
            this.mnuMain.PerformLayout();
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.toolStrip.ResumeLayout(false);
            this.toolStrip.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bnvMain)).EndInit();
            this.bnvMain.ResumeLayout(false);
            this.bnvMain.PerformLayout();
            this.tbcData.ResumeLayout(false);
            this.tpgStudents.ResumeLayout(false);
            this.tpgMarks.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgvMarks)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bnsMarks)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.studentBindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvMain;
        private System.Windows.Forms.BindingSource bnsDataGrid;
        private System.Windows.Forms.MenuStrip mnuMain;
        private System.Windows.Forms.ToolStripMenuItem mniFile;
        private System.Windows.Forms.ToolStripMenuItem mniExit;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel statusBar;
        private System.Windows.Forms.ToolStrip toolStrip;
        private System.Windows.Forms.ToolStripMenuItem mniNew;
        private System.Windows.Forms.ToolStripMenuItem mniLoad;
        private System.Windows.Forms.ToolStripMenuItem mniSave;
        private System.Windows.Forms.ToolStripSeparator mniSep1;
        private System.Windows.Forms.SaveFileDialog sfdStudents;
        private System.Windows.Forms.OpenFileDialog ofdStudents;
        private System.Windows.Forms.BindingNavigator bnvMain;
        private System.Windows.Forms.ToolStripButton bindingNavigatorAddNewItem;
        private System.Windows.Forms.ToolStripLabel bindingNavigatorCountItem;
        private System.Windows.Forms.ToolStripButton bindingNavigatorDeleteItem;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMoveFirstItem;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMovePreviousItem;
        private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator;
        private System.Windows.Forms.ToolStripTextBox bindingNavigatorPositionItem;
        private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator1;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMoveNextItem;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMoveLastItem;
        private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator2;
        private System.Windows.Forms.ToolStripButton tsbNew;
        private System.Windows.Forms.ToolStripButton tsbLoad;
        private System.Windows.Forms.ToolStripButton tsbSave;
        private System.Windows.Forms.ToolStripButton tsbExit;
        private System.Windows.Forms.ToolStripMenuItem справкаToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem оПрограммеToolStripMenuItem;
        private System.Windows.Forms.ToolStripStatusLabel statusBar2;
        private System.Windows.Forms.TabControl tbcData;
        private System.Windows.Forms.TabPage tpgStudents;
        private System.Windows.Forms.TabPage tpgMarks;
        private System.Windows.Forms.DataGridView dgvMarks;
        private System.Windows.Forms.BindingSource bnsMarks;
        private System.Windows.Forms.DataGridViewComboBoxColumn dgcSubject;
        private System.Windows.Forms.DataGridViewComboBoxColumn dgcLevel;
        private System.Windows.Forms.Label lblSurname;
        private System.Windows.Forms.BindingSource studentBindingSource;
        private System.Windows.Forms.DataGridViewTextBoxColumn dgcId;
        private System.Windows.Forms.DataGridViewTextBoxColumn dgcSurname;
        private System.Windows.Forms.DataGridViewComboBoxColumn dgcGender;
        private System.Windows.Forms.DataGridViewTextBoxColumn dgcBirthDate;
        private System.Windows.Forms.DataGridViewComboBoxColumn dgcCourse;
        private System.Windows.Forms.DataGridViewComboBoxColumn dgcGroup;
        private System.Windows.Forms.DataGridViewCheckBoxColumn dgcScholarship;
        private System.Windows.Forms.DataGridViewTextBoxColumn dgcAvgLevel;
        private System.Windows.Forms.ToolStripMenuItem mniData;
        private System.Windows.Forms.ToolStripMenuItem mniSort;
        private System.Windows.Forms.ToolStripMenuItem mniSurname;
        private System.Windows.Forms.ToolStripMenuItem mniAvgLevel;
    }
}


namespace ListViewShip.Forms
{
    partial class EditForm
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
            if (disposing && (components != null)) {
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EditForm));
            this.grbData = new System.Windows.Forms.GroupBox();
            this.btnPhotoChoice = new System.Windows.Forms.Button();
            this.txbMaxSpeed = new System.Windows.Forms.TextBox();
            this.lblMaxSpeed = new System.Windows.Forms.Label();
            this.txbCruisingRange = new System.Windows.Forms.TextBox();
            this.lblCruiseRange = new System.Windows.Forms.Label();
            this.txbDisplacement = new System.Windows.Forms.TextBox();
            this.lblDisplacement = new System.Windows.Forms.Label();
            this.txbName = new System.Windows.Forms.TextBox();
            this.lblName = new System.Windows.Forms.Label();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnSaveOk = new System.Windows.Forms.Button();
            this.grbPhoto = new System.Windows.Forms.GroupBox();
            this.pbxPhoto = new System.Windows.Forms.PictureBox();
            this.ofdPhoto = new System.Windows.Forms.OpenFileDialog();
            this.grbData.SuspendLayout();
            this.grbPhoto.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbxPhoto)).BeginInit();
            this.SuspendLayout();
            // 
            // grbData
            // 
            this.grbData.Controls.Add(this.btnPhotoChoice);
            this.grbData.Controls.Add(this.txbMaxSpeed);
            this.grbData.Controls.Add(this.lblMaxSpeed);
            this.grbData.Controls.Add(this.txbCruisingRange);
            this.grbData.Controls.Add(this.lblCruiseRange);
            this.grbData.Controls.Add(this.txbDisplacement);
            this.grbData.Controls.Add(this.lblDisplacement);
            this.grbData.Controls.Add(this.txbName);
            this.grbData.Controls.Add(this.lblName);
            this.grbData.Controls.Add(this.btnCancel);
            this.grbData.Controls.Add(this.btnSaveOk);
            resources.ApplyResources(this.grbData, "grbData");
            this.grbData.Name = "grbData";
            this.grbData.TabStop = false;
            // 
            // btnPhotoChoice
            // 
            resources.ApplyResources(this.btnPhotoChoice, "btnPhotoChoice");
            this.btnPhotoChoice.Name = "btnPhotoChoice";
            this.btnPhotoChoice.UseVisualStyleBackColor = true;
            this.btnPhotoChoice.Click += new System.EventHandler(this.btnPhotoChoice_Click);
            // 
            // txbMaxSpeed
            // 
            resources.ApplyResources(this.txbMaxSpeed, "txbMaxSpeed");
            this.txbMaxSpeed.Name = "txbMaxSpeed";
            this.txbMaxSpeed.TextChanged += new System.EventHandler(this.txbAll_TextChanged);
            // 
            // lblMaxSpeed
            // 
            resources.ApplyResources(this.lblMaxSpeed, "lblMaxSpeed");
            this.lblMaxSpeed.Name = "lblMaxSpeed";
            // 
            // txbCruisingRange
            // 
            resources.ApplyResources(this.txbCruisingRange, "txbCruisingRange");
            this.txbCruisingRange.Name = "txbCruisingRange";
            this.txbCruisingRange.TextChanged += new System.EventHandler(this.txbAll_TextChanged);
            // 
            // lblCruiseRange
            // 
            resources.ApplyResources(this.lblCruiseRange, "lblCruiseRange");
            this.lblCruiseRange.Name = "lblCruiseRange";
            // 
            // txbDisplacement
            // 
            resources.ApplyResources(this.txbDisplacement, "txbDisplacement");
            this.txbDisplacement.Name = "txbDisplacement";
            this.txbDisplacement.TextChanged += new System.EventHandler(this.txbAll_TextChanged);
            // 
            // lblDisplacement
            // 
            resources.ApplyResources(this.lblDisplacement, "lblDisplacement");
            this.lblDisplacement.Name = "lblDisplacement";
            // 
            // txbName
            // 
            resources.ApplyResources(this.txbName, "txbName");
            this.txbName.Name = "txbName";
            this.txbName.TextChanged += new System.EventHandler(this.txbAll_TextChanged);
            // 
            // lblName
            // 
            resources.ApplyResources(this.lblName, "lblName");
            this.lblName.Name = "lblName";
            // 
            // btnCancel
            // 
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            resources.ApplyResources(this.btnCancel, "btnCancel");
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            // 
            // btnSaveOk
            // 
            this.btnSaveOk.DialogResult = System.Windows.Forms.DialogResult.OK;
            resources.ApplyResources(this.btnSaveOk, "btnSaveOk");
            this.btnSaveOk.Name = "btnSaveOk";
            this.btnSaveOk.UseVisualStyleBackColor = true;
            // 
            // grbPhoto
            // 
            this.grbPhoto.Controls.Add(this.pbxPhoto);
            resources.ApplyResources(this.grbPhoto, "grbPhoto");
            this.grbPhoto.Name = "grbPhoto";
            this.grbPhoto.TabStop = false;
            // 
            // pbxPhoto
            // 
            resources.ApplyResources(this.pbxPhoto, "pbxPhoto");
            this.pbxPhoto.Name = "pbxPhoto";
            this.pbxPhoto.TabStop = false;
            // 
            // ofdPhoto
            // 
            resources.ApplyResources(this.ofdPhoto, "ofdPhoto");
            // 
            // EditForm
            // 
            this.AcceptButton = this.btnSaveOk;
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btnCancel;
            this.Controls.Add(this.grbPhoto);
            this.Controls.Add(this.grbData);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "EditForm";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.grbData.ResumeLayout(false);
            this.grbData.PerformLayout();
            this.grbPhoto.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pbxPhoto)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grbData;
        private System.Windows.Forms.TextBox txbName;
        private System.Windows.Forms.Label lblName;
        private System.Windows.Forms.Button btnSaveOk;
        private System.Windows.Forms.GroupBox grbPhoto;
        private System.Windows.Forms.Button btnPhotoChoice;
        private System.Windows.Forms.TextBox txbMaxSpeed;
        private System.Windows.Forms.Label lblMaxSpeed;
        private System.Windows.Forms.TextBox txbCruisingRange;
        private System.Windows.Forms.Label lblCruiseRange;
        private System.Windows.Forms.TextBox txbDisplacement;
        private System.Windows.Forms.Label lblDisplacement;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.PictureBox pbxPhoto;
        private System.Windows.Forms.OpenFileDialog ofdPhoto;
    }
}
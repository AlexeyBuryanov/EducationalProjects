using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DataGridView_DataBinding
{
    public partial class AboutForm : Form
    {
        public AboutForm()
        {
            InitializeComponent();
        } // AboutForm

        private void AboutForm_Click(object sender, EventArgs e)
        {
            Hide();
        } // AboutForm_Click
    }
}

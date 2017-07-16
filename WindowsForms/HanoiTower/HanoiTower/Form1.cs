using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HanoiTower
{
    public partial class Form1 : Form
    {
        private int count;
        private int minMoves;


        public Form1()
        {
            InitializeComponent();
            groupBox1.AllowDrop = groupBox2.AllowDrop = groupBox3.AllowDrop = true;
        } // Form1


        private void Form1_Load(object sender, EventArgs e)
        {
            Random rand = new Random();
            int n = (int)numericUpDown1.Value;
            for (int i = 0; i < n; i++) {
                Label lb = new Label();
                lb.BorderStyle = BorderStyle.FixedSingle;
                lb.BackColor = Color.FromArgb(rand.Next(256), rand.Next(256), rand.Next(256));
                lb.Size = new Size((groupBox1.Width - 10) * (n - i) / n, (groupBox1.Height - 15) / n);
                lb.Location = new Point((groupBox1.Width - lb.Width) / 2, groupBox1.Height - 2 - (i + 1) * lb.Height);
                lb.MouseDown += label_MouseDown;
                groupBox1.Controls.Add(lb); 
            } // for i

            count = 0;                            
            minMoves = (int)Math.Pow(2, n) - 1;   
            ShowMovesCounter();     

            label2.Visible = false;
        } // Form1_Load


        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            label_Dispose(groupBox1);
            label_Dispose(groupBox2);
            label_Dispose(groupBox3);

            Form1_Load(this, EventArgs.Empty);  
        } // numericUpDown1_ValueChanged


        private void label_Dispose(GroupBox gb)
        {
            for (int i = gb.Controls.Count - 1; i >= 0; i--) gb.Controls[i].Dispose();
        } // label_Dispose


        private void label_MouseDown(object sender, MouseEventArgs e)
        {
            if (!button1.Enabled) return;

            if (e.Button == MouseButtons.Left)
                DoDragDrop(sender, DragDropEffects.Move);
        } // label_MouseDown


        private void groupBox1_DragEnter(object sender, DragEventArgs e)
        {
            if (label2.Visible) {                  
                e.Effect = DragDropEffects.None;          
                return;
            } // if

            int widthTopBlock = int.MaxValue;

            GroupBox gb = sender as GroupBox;
            if (gb.Controls.Count > 0)
                widthTopBlock = gb.Controls[gb.Controls.Count - 1].Width;

            Label lb = e.Data.GetData(typeof(Label)) as Label;
            if (lb != lb.Parent.Controls[lb.Parent.Controls.Count - 1] || 
                lb.Width > widthTopBlock)
                e.Effect = DragDropEffects.None;
            else
                e.Effect = DragDropEffects.Move;
        } // groupBox1_DragEnter


        private void groupBox1_DragDrop(object sender, DragEventArgs e)
        {
            Label lb = e.Data.GetData(typeof(Label)) as Label;
            GroupBox gb = sender as GroupBox;                     

            if (gb == lb.Parent) return;

            label_Move(lb, gb);
        } // groupBox1_DragDrop


        private void label_Move(Label lb, GroupBox gb)
        {
            lb.Parent = gb;
            lb.Top = gb.Height - 2 - gb.Controls.Count * lb.Height;
            count++;
            ShowMovesCounter();
            label2.Visible = groupBox3.Controls.Count == numericUpDown1.Value; 
        } // label_Move


        private void ShowMovesCounter()
        {
            label1.Text = $"Количество ходов: {count} (минимально: {minMoves})";
        } // ShowMovesCounter


        private void button2_Click(object sender, EventArgs e)
        {
            numericUpDown1.Enabled = button1.Enabled = false;

            if (groupBox1.Controls.Count != numericUpDown1.Value) {
                numericUpDown1_ValueChanged(null, null);            
                Application.DoEvents();
                Thread.Sleep(800);
            } // if
            
            Step((int)numericUpDown1.Value, groupBox1, groupBox3, groupBox2);
            numericUpDown1.Enabled = button1.Enabled = true;
        } // button2_Click


        // n - количество собираемых блоков
        // src - исходная башня
        // dst - результирующая башня, в ней собираем блоки
        // tmp - вспомогательная башня, помогает сборке
        private void Step(int n, GroupBox src, GroupBox dst, GroupBox tmp)
        {
            if (n == 0) return;

            Step(n-1, src, tmp, dst);

            if (button1.Enabled) return;

            label_Move(src.Controls[src.Controls.Count-1] as Label, dst);
            Application.DoEvents(); 
            Thread.Sleep(1500 / ((int)numericUpDown1.Value));

            Step(n - 1, tmp, dst, src);
        } // Step


        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            button1.Enabled = true;
        } // Form1_FormClosed
    } // class Form1
}

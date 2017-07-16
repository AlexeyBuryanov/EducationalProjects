using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Work_with_ListBox
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        } // FormMain


        // Добавить введённую строку в лист-бокс 1
        private void buttonAddListBox1_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBox.Text)) {
                MessageBox.Show("Я не могу принять пустую строку!",
                    "Лист-бокс №1", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            } // if

            listBox1.Items.Add(textBox.Text);
        } // buttonAddListBox1_Click


        // Добавить введённую строку в лист-бокс 2
        private void buttonAddListBox2_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBox.Text)) {
                MessageBox.Show("Я не могу принять пустую строку!",
                    "Лист-бокс №2", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            } // if

            listBox2.Items.Add(textBox.Text);
        } // buttonAddListBox2_Click


        // Копировать строку из 1-го ЛБ во 2-ой ЛБ
        private void buttonCopyToLB2_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem == null) {
                MessageBox.Show("Ни один элемент не был выбран.\nКопирование в лист-бокс №2 невозможно осуществить.",
                    "Лист-бокс №1", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation);
                return;
            } // if

            listBox2.Items.Add(listBox1.SelectedItem);
        } // buttonCopyToLB2_Click


        // Переместить строку из 1-го ЛБ во 2-ой ЛБ
        private void buttonMoveToLB2_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem == null) {
                MessageBox.Show("Ни один элемент не был выбран.\nКопирование в лист-бокс №2 невозможно осуществить.",
                    "Лист-бокс №1", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation);
                return;
            } // if

            listBox2.Items.Add(listBox1.SelectedItem);
            listBox1.Items.Remove(listBox1.SelectedItem);
        } // buttonMoveToLB2_Click


        // Копировать строку из 2-го ЛБ в 1-ый ЛБ
        private void buttonCopyToLB1_Click(object sender, EventArgs e)
        {
            if (listBox2.SelectedItem == null) {
                MessageBox.Show("Ни один элемент не был выбран.\nКопирование в лист-бокс №1 невозможно осуществить.",
                    "Лист-бокс №2", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation);
                return;
            } // if

            listBox1.Items.Add(listBox2.SelectedItem);
        } // buttonCopyToLB1_Click


        // Переместить строку из 2-го ЛБ в 1-ый ЛБ
        private void buttonMoveToLB1_Click(object sender, EventArgs e)
        {
            if (listBox2.SelectedItem == null) {
                MessageBox.Show("Ни один элемент не был выбран.\nПеремещение в лист-бокс №1 невозможно осуществить.",
                    "Лист-бокс №2", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation);
                return;
            } // if

            listBox1.Items.Add(listBox2.SelectedItem);
            listBox2.Items.Remove(listBox2.SelectedItem);
        } // buttonMoveToLB1_Click


        // При выборе значения в ЛБ №1
        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem != null) {
                buttonCopyToLB2.Enabled = true;
                buttonMoveToLB2.Enabled = true;
            } // if
        } // listBox1_SelectedIndexChanged


        // При выборе значения в ЛБ №2
        private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox2.SelectedItem != null) {
                buttonCopyToLB1.Enabled = true;
                buttonMoveToLB1.Enabled = true;
            } // if
        } // listBox2_SelectedIndexChanged


        // Очистить первый список
        private void buttonClearLB1_Click(object sender, EventArgs e)
        {
            if (listBox1.Items.Count != 0) {
                listBox1.Items.Clear();
                buttonCopyToLB2.Enabled = false;
                buttonMoveToLB2.Enabled = false;
            } else
                MessageBox.Show("Список и так уже пустой!",
                    "Лист-бокс №1", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation);
        } // buttonClearLB1_Click


        // Очистить второй список
        private void buttonClearLB2_Click(object sender, EventArgs e)
        {
            if (listBox2.Items.Count != 0) {
                listBox2.Items.Clear();
                buttonCopyToLB1.Enabled = false;
                buttonMoveToLB1.Enabled = false;
            } else
                MessageBox.Show("Список и так уже пустой!",
                    "Лист-бокс №2", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation);
        } // buttonClearLB2_Click


        // Очистить всё
        private void buttonClearAll_Click(object sender, EventArgs e)
        {
            if (!(listBox1.Items.Count == 0 && listBox2.Items.Count == 0 && string.IsNullOrWhiteSpace(textBox.Text))) {
                listBox1.Items.Clear();
                listBox2.Items.Clear();
                textBox.Clear();
                buttonCopyToLB1.Enabled = buttonMoveToLB1.Enabled = 
                    buttonCopyToLB2.Enabled = buttonMoveToLB2.Enabled = false;
            } else
                MessageBox.Show("Нечего больше удалять!",
                    "Система", MessageBoxButtons.OKCancel, MessageBoxIcon.Hand);
        } // buttonClearAll_Click
    } // class FormMain
}

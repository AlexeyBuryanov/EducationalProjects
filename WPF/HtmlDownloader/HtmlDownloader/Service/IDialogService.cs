﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HtmlDownloader
{
    public interface IDialogService
    {
        void ShowError(string message);
        string FilePath { get; set; }       // путь к выбранному файлу
        bool OpenFileDialog();              // открытие файла
        bool SaveFileDialog();              // сохранение файла
    } // IDialogService
} // HtmlDownloader
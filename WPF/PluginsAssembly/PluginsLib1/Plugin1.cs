using System.Windows;
using System.Windows.Shell;

namespace PluginsLib1
{
    public class Plugin1
    {
        /// <summary>
        /// Меняет стиль окна
        /// </summary>
        public void SetWindowStyle(Window win)
        {
            var style = new Style(typeof(Window));
            style.Setters.Add(new Setter(Window.WindowStyleProperty, WindowStyle.None));
            var wh = new WindowChrome {
                CaptionHeight = 30,
                NonClientFrameEdges = NonClientFrameEdges.None,
                GlassFrameThickness = new Thickness(1, 1, 1, 1),
                ResizeBorderThickness = new Thickness(7, 7, 7, 7),
                UseAeroCaptionButtons = false
            };
            style.Setters.Add(new Setter(WindowChrome.WindowChromeProperty, wh));
            win.Style = style;
        } // SetWindowStyle
    } // Plugin1
} // PluginsLib1
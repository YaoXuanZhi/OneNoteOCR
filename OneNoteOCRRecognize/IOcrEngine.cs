using System;
using System.Drawing;
using System.Linq;



namespace OneNoteOCRRecognize
{
    //interface IOcrEngine
    public interface IOcrEngine
    {
        string Recognize(Image image);
    }
}



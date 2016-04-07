//关于OneNote OCR部分代码来源于Github：https://github.com/matthiaswelz/journeyofcode/tree/master/OneNoteOCR
//有关此Github项目的详细介绍，请访问：http://www.journeyofcode.com/free-easy-ocr-c-using-onenote/
using System;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Drawing.Imaging;



namespace OneNoteOCRRecognize
{
    public class OcrCommonAPI
    {
        //识别本地磁盘中的图像，必须将导出到C/C++的函数设置为静态函数，并且为公有
        public static string OCRPictrueInDisk(string PicturePath)
        {
            Image image = Image.FromFile(PicturePath);
            try
            {
                using (var ocrEngine = new OneNoteOcrEngine())
                    if (!image.Equals(null))
                    {
                        var text = ocrEngine.Recognize(image);
                        if (text != null)
                        {
                            //Console.WriteLine("OcrException:\n");
                            return text;
                        }
                    }
            }
            catch (OcrException ex)
            {
                Console.WriteLine("OcrException:\n" + ex);
            }
            catch (Exception ex)
            {
                Console.WriteLine("General Exception:\n" + ex);
            }

            return "Error";
        }

        //识别内存中图像Base64编码后的数据，必须将导出到C/C++的函数设置为静态函数，并且为公有
        public static string OCRPictrueInMemory(string Base64Data)
        {
            Image image = Image2Bytes.BytesToImage(Convert.FromBase64String(Base64Data));
            try
            {
                using (var ocrEngine = new OneNoteOcrEngine())
                    if (!image.Equals(null))
                    {
                        var text = ocrEngine.Recognize(image);
                        if (text != null)
                        {
                            //Console.WriteLine("OcrRecognizeResult:\n");
                            return text;
                        }
                    }
            }
            catch (OcrException ex)
            {
                Console.WriteLine("OcrException:\n" + ex);
            }
            catch (Exception ex)
            {
                Console.WriteLine("General Exception:\n" + ex);
            }
            return "Error";
        }


    }
}

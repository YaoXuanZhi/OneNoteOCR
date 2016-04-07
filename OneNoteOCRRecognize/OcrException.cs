﻿using System;
using System.Runtime.Serialization;
namespace OneNoteOCRRecognize
{
    [Serializable]
    public class OcrException
        : Exception
    //class OcrException : Exception
    {
        public OcrException()
            : this("General error during OCR.")
        {
            
        }

        public OcrException(string message) : base(message)
        {
        }

        public OcrException(string message, Exception innerException) : base(message, innerException)
        {
        }

        protected OcrException(SerializationInfo info, StreamingContext context) : base(info, context)
        {
        }
    }
}
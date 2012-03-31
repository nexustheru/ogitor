/*/////////////////////////////////////////////////////////////////////////////////
/// An
///    ___   ____ ___ _____ ___  ____
///   / _ \ / ___|_ _|_   _/ _ \|  _ \
///  | | | | |  _ | |  | || | | | |_) |
///  | |_| | |_| || |  | || |_| |  _ <
///   \___/ \____|___| |_| \___/|_| \_\
///                              File
///
/// Copyright (c) 2008-2012 Ismail TARIM <ismail@royalspor.com> and the Ogitor Team
//
/// The MIT License
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
////////////////////////////////////////////////////////////////////////////////*/

#ifndef I_IMAGE_EDITOR_CODEC_HXX
#define I_IMAGE_EDITOR_CODEC_HXX

#include <QtCore/QString>
#include <QtGui/QContextMenuEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QScrollArea>

#include <Ogre.h>

//----------------------------------------------------------------------------------------

class GenericImageEditorDocument;

//----------------------------------------------------------------------------------------

class IImageEditorCodec
{
public:
    IImageEditorCodec(GenericImageEditorDocument* genImgEdDoc, QString docName, QString documentIcon)
    {
        mGenImgEdDoc        = genImgEdDoc;
        mDocName            = docName;
        mDocumentIcon       = documentIcon;
        mBuffer             = 0;
    }

    virtual ~IImageEditorCodec()
    {
        delete [] mBuffer;
        mBuffer = 0;
    }

    /**
    * Called when preparing to display the image
    * @param stream data stream of the image
    * @return the pixmap that is now going to be displayed.               
    */
    virtual QPixmap*    onBeforeDisplay(Ogre::DataStreamPtr stream) = 0;

    /**
    * Called after the content was displayed for the first time            
    */
    virtual void        onAfterDisplay(){};

    /**
    * Called when a context menu request was triggered.
    */
    virtual void        onContextMenu(QContextMenuEvent* event){};

    /**
    * Called when a tool tip display is requested
    */
    virtual QString     onToolTip(QMouseEvent* event){return QString("");};

    /**
    * Called whenever an image that is already open in one tab is requested to be displayed again
    * and therefore will be moved to the foreground. 
    */
    virtual void        onDisplayRequest(){};

    /**
    * Called whenever the image this codec instance is attached to is made visible due to a tab change.
    */
    virtual void        onTabChange(){};

    /**
    * Called whenever the image this codec instance is attached to is being closed. At this stage 
    * at runtime the image was already requested to be saved if there were unsaved changes, so
    * no need to do this again in this method.
    */
    virtual void        onClose(){};

    QString             getDocumentIcon(){return mDocumentIcon;}

protected:
    GenericImageEditorDocument*     mGenImgEdDoc;
    unsigned char*                  mBuffer;
    QImage                          mImage;
    QString                         mDocName;
    QString                         mDocumentIcon;
};

//----------------------------------------------------------------------------------------

class IImageEditorCodecFactory
{
public:
    virtual IImageEditorCodec* create(GenericImageEditorDocument* genImgEdDoc, QString docName) = 0;
};

//----------------------------------------------------------------------------------------

#endif

//----------------------------------------------------------------------------------------
/*
* Copyright (C) 2020 Centre National d'Etudes Spatiales (CNES)
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/
/************************************************************************************************************
 *                                                                                                          *
 *                                ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo         *
 *                             o                                                                            *
 *                          o                                                                               *
 *                        o                                                                                 *
 *                      o                                                                                   *
 *                     o       ooooooo       ooooooo    o         o      oo                                 *
 *    o              o       o        o     o       o   o         o     o   o                               *
 *      o           o       o          o   o         o  o         o    o      o                             *
 *        o        o       o           o   o         o  o         o    o        o                           *
 *         o      o        o      oooo     o         o  o         o   o           o                         *
 *          o    o          o              o         o  o         o   o           o                         *
 *           o  o            o             o         o  o o      o   o          o                           *
 *            oo              oooooooo    o         o   o  oooooo   o      oooo                             *
 *                                                     o                                                    *
 *                                                     o                                                    *
 *                                                    o                            o                        *
 *                                                    o            o      oooo     o   o      oooo          *
 *                                                   o             o         o    o    o         o          *
 *                                                   o            o       ooo     o   o       ooo           *
 *                                                               o       o       o   o          o           *
 *                                                               ooooo   oooo    o   ooooo  oooo            *
 *                                                                              o                           *
 *                                                                                                          *
 ************************************************************************************************************
 *                                                                                                          *
 * Author: CS Systemes d'Information  (France)                                                              *
 *                                                                                                          *
 ************************************************************************************************************
 * HISTORIQUE                                                                                               *
 *                                                                                                          *
 * VERSION : 5-1-0 : FA : LAIG-FA-MAC-145739-CS : 27 juin 2016 : Audit code - Supp de la macro ITK_EXPORT   *
 * VERSION : 1-0-0 : <TypeFT> : <NumFT> : 29 novembre 2010 : Creation
 *                                                                                                          *
 * FIN-HISTORIQUE                                                                                           *
 *                                                                                                          *
 * $Id$
 *                                                                                                          *
 ************************************************************************************************************/
#ifndef __vnsMultiChannelExtractROI_h
#define __vnsMultiChannelExtractROI_h

#include "otbExtractROIBase.h"
#include "otbVectorImage.h"

#include "itkMacro.h"
#include <vector>

namespace vns
{

/** \class MultiChannelExtractROI
 * \brief Extract a spatial or spectral subset of a multi-channel image.
 *
 * It is possible to extract all the channels from the input image or only those specified by the user.
 * The SetChannel() method allows to select one channel.
 * The SetFirstChannel() and SetLastChannel() methods allow the user to define a list of channels.
 *
 * \note If no channels are specified, then all channels from the input image are selected.
 * \note The image manipulated inside this class are of type otb::VectorImage.
 */
template <class TInputPixelType, class TOutputPixelType>
class MultiChannelExtractROI :
  public otb::ExtractROIBase<otb::VectorImage<TInputPixelType, 2>, otb::VectorImage<TOutputPixelType, 2> >
{
public:
  /** Standard class typedefs. */
  typedef MultiChannelExtractROI                                                             Self;
  typedef otb::ExtractROIBase<otb::VectorImage<TInputPixelType, 2>, otb::VectorImage<TOutputPixelType, 2> > Superclass;
  typedef itk::SmartPointer<Self>                                                            Pointer;
  typedef itk::SmartPointer<const Self>                                                      ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MultiChannelExtractROI, ExtractROIBase);

  /** Image type information. */
  typedef typename Superclass::InputImageType  InputImageType;
  typedef typename Superclass::OutputImageType OutputImageType;

  /** Pixel type information */
  typedef typename OutputImageType::InternalPixelType OutputValueType;

  /** Typedef to describe the output and input image region types. */
  typedef typename OutputImageType::RegionType OutputImageRegionType;
  typedef typename InputImageType::RegionType  InputImageRegionType;

  /** Typedef to describe the type of pixel. */
  typedef typename OutputImageType::PixelType OutputImagePixelType;
  typedef typename InputImageType::PixelType  InputImagePixelType;

  /** Typedef to describe the output and input image index and size types. */
  typedef typename OutputImageType::IndexType OutputImageIndexType;
  typedef typename InputImageType::IndexType  InputImageIndexType;
  typedef typename OutputImageType::SizeType  OutputImageSizeType;
  typedef typename InputImageType::SizeType   InputImageSizeType;

  void SetFirstChannel(unsigned int id);
  itkGetConstMacro(FirstChannel, unsigned int);
  void SetLastChannel(unsigned int id);
  itkGetConstMacro(LastChannel, unsigned int);

  /** MultiChannelExtractROI can produce an image which is a different
   * resolution than its input image.  As such, MultiChannelExtractROI
   * needs to provide an implementation for
   * GenerateOutputInformation() in order to inform the pipeline
   * execution model.  The original documentation of this method is
   * below.
   *
   * \sa ProcessObject::GenerateOutputInformaton()  */
  virtual void GenerateOutputInformation();

  /** Typedef Liste des canaux */
  typedef typename std::vector<unsigned int> ChannelsType;

  /** \return The list of processed channels */
  ChannelsType GetChannels() const
  {
    return (m_Channels);
  }

  /** \return The number of processed channels */
  unsigned int GetNbChannels() const
  {
    return (m_Channels.size());
  }

  /** Select a channel to process
   \param channel The channel to process */
  void SetChannel(unsigned int channel);

  /** Clear channels selection */
  void ClearChannels(void);

  /** ImageDimension enumeration */
  itkStaticConstMacro(InputImageDimension, unsigned int,
                      InputImageType::ImageDimension);
  itkStaticConstMacro(OutputImageDimension, unsigned int,
                      OutputImageType::ImageDimension);

protected:
  MultiChannelExtractROI();
  virtual ~MultiChannelExtractROI() {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const;

  /** Reinitialize channels vector for multiple Update.*/
  void ChannelsReInitialization();
  /** If the user set m_First/LastChannel, chack avaliability or fill m_Channels Work.*/
  void SetChannelsWorkWithLimits();

  /** ExtractImageFilter can be implemented as a  multithreaded filter.
   * \sa ImageToImageFilter::ThreadedGenerateData(),
   *     ImageToImageFilter::GenerateData()  */
  void ThreadedGenerateData(const OutputImageRegionType& outputRegionForThread,
                            itk::ThreadIdType threadId);

private:
  MultiChannelExtractROI(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  /** First/ last channel to process [1...] */
  unsigned int m_FirstChannel;
  unsigned int m_LastChannel;
  /** List of channels to process  [1...] */
  ChannelsType m_Channels;
  /** List of channels actually being processed [1...] */
  ChannelsType m_ChannelsWorks;
  /** Used to know if the user has set m_First/LastChannel (1) or m_Channels (3)*/
  int m_ChannelsKind;
};

} // end namespace otb

#ifndef VNS_MANUAL_INSTANTIATION
#include "vnsMultiChannelExtractROI.txx"
#endif

#endif

// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file carrier_message_pub_sub_types.cpp
 * This header file contains the implementation of the serialization functions.
 *
 * This file was generated by the tool fastcdrgen.
 */

#include "carrier_message_pub_sub_types.h"

#include <fastcdr/Cdr.h>
#include <fastcdr/FastBuffer.h>

using SerializedPayload_t = eprosima::fastrtps::rtps::SerializedPayload_t;
using InstanceHandle_t = eprosima::fastrtps::rtps::InstanceHandle_t;

namespace hermaeus {
namespace core {

CarrierMessagePubSubType::CarrierMessagePubSubType() {
  setName("CarrierMessage");
  auto type_size = CarrierMessage::getMaxCdrSerializedSize();
  type_size += eprosima::fastcdr::Cdr::alignment(
      type_size, 4); /* possible submessage alignment */
  m_typeSize = static_cast<uint32_t>(type_size) + 4; /*encapsulation*/
  m_isGetKeyDefined = CarrierMessage::isKeyDefined();
  size_t keyLength = CarrierMessage::getKeyMaxCdrSerializedSize() > 16
                         ? CarrierMessage::getKeyMaxCdrSerializedSize()
                         : 16;
  m_keyBuffer = reinterpret_cast<unsigned char*>(malloc(keyLength));
  memset(m_keyBuffer, 0, keyLength);
}

CarrierMessagePubSubType::~CarrierMessagePubSubType() {
  if (m_keyBuffer != nullptr) {
    free(m_keyBuffer);
  }
}

bool CarrierMessagePubSubType::serialize(void* data,
                                         SerializedPayload_t* payload) {
  CarrierMessage* p_type = static_cast<CarrierMessage*>(data);

  // Object that manages the raw buffer.
  eprosima::fastcdr::FastBuffer fastbuffer(
      reinterpret_cast<char*>(payload->data), payload->max_size);
  // Object that serializes the data.
  eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
                             eprosima::fastcdr::Cdr::DDS_CDR);
  payload->encapsulation =
      ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE
                                                                 : CDR_LE;
  // Serialize encapsulation
  ser.serialize_encapsulation();

  try {
    // Serialize the object.
    p_type->serialize(ser);
  } catch (
      eprosima::fastcdr::exception::NotEnoughMemoryException& /*exception*/) {
    return false;
  }

  // Get the serialized length
  payload->length = static_cast<uint32_t>(ser.getSerializedDataLength());
  return true;
}

bool CarrierMessagePubSubType::deserialize(SerializedPayload_t* payload,
                                           void* data) {
  // Convert DATA to pointer of your type
  CarrierMessage* p_type = static_cast<CarrierMessage*>(data);

  // Object that manages the raw buffer.
  eprosima::fastcdr::FastBuffer fastbuffer(
      reinterpret_cast<char*>(payload->data), payload->length);

  // Object that deserializes the data.
  eprosima::fastcdr::Cdr deser(fastbuffer,
                               eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
                               eprosima::fastcdr::Cdr::DDS_CDR);

  // Deserialize encapsulation.
  deser.read_encapsulation();
  payload->encapsulation =
      deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE
                                                                   : CDR_LE;

  try {
    // Deserialize the object.
    p_type->deserialize(deser);
  } catch (
      eprosima::fastcdr::exception::NotEnoughMemoryException& /*exception*/) {
    return false;
  }

  return true;
}

std::function<uint32_t()> CarrierMessagePubSubType::getSerializedSizeProvider(
    void* data) {
  return [data]() -> uint32_t {
    return static_cast<uint32_t>(type::getCdrSerializedSize(
               *static_cast<CarrierMessage*>(data))) +
           4u /*encapsulation*/;
  };
}

void* CarrierMessagePubSubType::createData() {
  return reinterpret_cast<void*>(new CarrierMessage());
}

void CarrierMessagePubSubType::deleteData(void* data) {
  delete (reinterpret_cast<CarrierMessage*>(data));
}

bool CarrierMessagePubSubType::getKey(void* data, InstanceHandle_t* handle,
                                      bool force_md5) {
  if (!m_isGetKeyDefined) {
    return false;
  }

  CarrierMessage* p_type = static_cast<CarrierMessage*>(data);

  // Object that manages the raw buffer.
  eprosima::fastcdr::FastBuffer fastbuffer(
      reinterpret_cast<char*>(m_keyBuffer),
      CarrierMessage::getKeyMaxCdrSerializedSize());

  // Object that serializes the data.
  eprosima::fastcdr::Cdr ser(fastbuffer,
                             eprosima::fastcdr::Cdr::BIG_ENDIANNESS);
  p_type->serializeKey(ser);
  if (force_md5 || CarrierMessage::getKeyMaxCdrSerializedSize() > 16) {
    m_md5.init();
    m_md5.update(m_keyBuffer,
                 static_cast<unsigned int>(ser.getSerializedDataLength()));
    m_md5.finalize();
    for (uint8_t i = 0; i < 16; ++i) {
      handle->value[i] = m_md5.digest[i];
    }
  } else {
    for (uint8_t i = 0; i < 16; ++i) {
      handle->value[i] = m_keyBuffer[i];
    }
  }
  return true;
}

}  // namespace core
}  // namespace hermaeus
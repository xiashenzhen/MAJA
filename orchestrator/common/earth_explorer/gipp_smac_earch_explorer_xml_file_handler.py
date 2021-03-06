# -*- coding: utf-8 -*-
#
# Copyright (C) 2020 Centre National d'Etudes Spatiales (CNES)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#
"""
###################################################################################################

                        o     o
                        oo   oo   oo        o   oo        ,-.
                        o o o o  o  o       o  o  o       \_/
                        o  o  o o    o      o o    o     {|||D
                        o     o oooooo      o oooooo      / \
                        o     o o    o o    o o    o      `-^
                        o     o o    o  oooo  o    o

###################################################################################################

orchestrator.common.earth_explorer.gipp_l2_comm_earth_explorer_xml_file_handler -- shortdesc

orchestrator.common.earth_explorer.gipp_l2_comm_earth_explorer_xml_file_handler is a description

It defines classes_and_methods


###################################################################################################
"""
from orchestrator.common.earth_explorer.earth_explorer_xml_file_handler import EarthExplorerXMLFileHandler
from orchestrator.common.xml_tools import get_only_value


SMAC_EARTH_EXPLORER_HANDLER_XPATH = {"NumberOfBands": "//SMAC_NumberOfBands",
                                     "Coefficients": "//SMAC_Coefficients"
                                     }


class GippSMACEarthExplorerXMLFileHandler(EarthExplorerXMLFileHandler):

    def __init__(self, gipp_filename, validate_schema=False, schema_path=None):
        super(GippSMACEarthExplorerXMLFileHandler, self).__init__(gipp_filename, validate_schema, schema_path)
        self.NumberOfBands = int(get_only_value(self.root, SMAC_EARTH_EXPLORER_HANDLER_XPATH["NumberOfBands"]).text)
        self.Coefficients = get_only_value(self.root, SMAC_EARTH_EXPLORER_HANDLER_XPATH["Coefficients"]).text

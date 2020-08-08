import os
import re
from fnmatch import fnmatch

from RdToMd import RdTemplate


class MdManager:

    def __init__(self, path_to_file, rd_dir_path):
        super(MdManager, self).__init__()
        self.path_to_file = path_to_file
        self.rd_dir_path = rd_dir_path
        self.is_file_read = False
        self.is_parsed = False
        self.origin_text = ""
        self.outline_list = {}
        self.accessories_list = {}

    def get_list(self):
        root = self.rd_dir_path
        pattern = "*.Rd"
        path_values = []

        for root_path, subdirs, files in os.walk(root):
            for f_name in files:

                if fnmatch(f_name, pattern):
                    f_name = os.path.splitext(f_name)[0]
                    path_values.append("[%s](#%s)<br>" % (f_name, f_name))

        return("\n".join(path_values))

    def start(self):
        self._parse(self._get_origin_text())
        text = "\n"
        for header_tupe in self.outline_list.keys():
            if not header_tupe == "__f":
                text += "## " + header_tupe + "\n\n"
            for function_name in self.outline_list[header_tupe]:
                a = RdTemplate(self.rd_dir_path + function_name + ".Rd")
                text += "### " + a.get_attr("Name") + "\n\n"
                if function_name in self.accessories_list:
                    text += self.accessories_list[function_name] + "\n"
                text += "#### Usage\n```R " + a.get_attr("Usage") + "```\n\n"
                text += "#### Arguments\n " + a.get_attr("Arguments") + "\n\n"
                text += "#### Return\n " + a.get_attr("Value") + "\n\n"
                text += "#### Description\n " + a.get_attr("Description") + "\n\n"
                text += "#### Examples\n```R " + a.get_attr("Examples") + "```\n<hr>\n\n"

        f = open(self.path_to_file, "w+")
        f.write(self.origin_text[:self.ds.end()] + text + self.origin_text[self.de.start():])
        f.close()

    def _get_origin_text(self):
        if not self.is_file_read:
            f = open(self.path_to_file, "r+")
            self.origin_text = f.read()
            self.is_file_read = True
            f.close()

        return self.origin_text

    def _parse(self, text):
        if self.is_parsed:
            return
        self.is_parsed = True
        os = re.search('<!--outline-start-->', text)
        oe = re.search('<!--outline-end-->', text)
        self._parse_outline(text[os.end()+1:oe.start()])
        self.ds = re.search('<!--doc-start-->', text)
        self.de = re.search('<!--doc-end-->', text)

    def _parse_outline(self, text):
        lines = re.split("\\n", text)
        self.outline_list  = {}
        ch = "__f"
        last_header = "__f"
        self.outline_list  = {ch : []}
        for line in lines:
            header = re.search("\[([^\]]+)\]", line)
            if header is not None:
                if line.startswith("###"):
                    ch = header.groups(0)[0]
                    self.outline_list[ch] = []
                else:
                    last_header = header.groups(0)[0]
                    self.outline_list[ch].append(last_header)
            accessory =  re.search('<!--accessory:\[(.+)\]-->', line)
            if accessory is not None:
                if not last_header in self.accessories_list:
                    self.accessories_list[last_header] = ""
                self.accessories_list[last_header] += accessory.groups(0)[0] + "\n"


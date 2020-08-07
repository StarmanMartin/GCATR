import re


class RdTemplate:

    def __init__(self, path_to_file):
        super(RdTemplate, self).__init__()
        self.path_to_file = path_to_file
        self.is_file_read = False
        self.is_parsed = False
        self.origin_text = ""
        self.parsed_text = {}

    def get_attr(self, attr_name):
        self._parse(self._get_origin_text())
        return self.parsed_text.get(attr_name, "\-")

    def _get_origin_text(self):
        if not self.is_file_read:
            f = open(self.path_to_file, 'r')
            self.origin_text = f.readlines()
            self.is_file_read = True
            f.close()

        return self.origin_text

    def _parse(self, text):
        if self.is_parsed:
            return
        self.is_parsed = True
        x = None
        tf = self._TagFinder()
        for line in text:
            if x is None:
                x = re.search("^\\\\(\w+){", line)
                tf.reset()
            if x is not None:
                tf.find_tag_content(line)
                if tf.is_done():
                    self.parsed_text[x.groups()[0].capitalize()] = self._parse_inner_text(tf.get_text())
                    x = None

    def _parse_inner_text(self, text):
        x = re.split("\\\\item", text)
        text = x[0]
        tf = self._TagFinder()
        for part in x[1:]:
            tf.reset()
            tf.find_tag_content(part)
            text += "*" + tf.get_text() + "*"
            s = part[tf.end_idx+1:]
            tf.reset()
            tf.find_tag_content(s)
            text += "\t" + tf.get_text() + "<br>"
            text += s[tf.end_idx + 1:]

        x = re.split("\\\\link|\\\\emph", text)
        text = x[0]
        for part in x[1:]:
            tf.reset()
            tf.find_tag_content(part)
            text += "*" + tf.get_text() + "*"
            text += part[tf.end_idx + 1:]

        text = text.replace("\\cr", "<br>")

        return text

    class _TagFinder:
        idx = 0
        text = ""
        end_idx = -1

        def reset(self):
            self.idx = 0
            self.end_idx =-1
            self.text = ""

        def find_tag_content(self, line):
            ignore_next = False
            counter = 0
            for letter in line:
                if not ignore_next and letter == "}":
                    self.idx -= 1

                if self.idx > 0:
                    self.text += letter
                elif len(self.text) > 0:
                    self.end_idx = counter
                    return

                if ignore_next:
                    ignore_next = False
                elif letter == "{":
                    self.idx += 1
                elif letter == "\\":
                    ignore_next = True

                counter += 1

        def is_done(self):
            return self.idx == 0

        def get_text(self):
            return self.text

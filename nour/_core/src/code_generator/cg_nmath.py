import textwrap
import os
import argparse
from typing import List, Dict

from common import *

SRC_C_FILE = os.path.join(NMATH_DIR, "math_basic.c.src")
SRC_H_FILE = os.path.join(NMATH_DIR, "math_basic.h.src")

DOC = """\
    /**
    * Performs `{LN}` on two input nodes with type {T} and stores the result in the output node.
    *
    * Parameters:
    *   - args: A pointer to `NFuncArgs`, containing:
    *       - nodes[0]: The first input node with type {T} (`n1`).
    *       - nodes[1]: The second input node with type {T} (`n2`).
    *       - out: The output node with type {T} to store the result.
    * Return:
    *   - 0 on success.
    *   - -1 if memory allocation or iteration fails.
    */
"""

class MathFunction:
    def __init__(self, name : str, longname : str, dtype : int):
        self.name = name
        self.longname = longname
        self.type = dtype2name[dtype]
        self.nr_type = dtype2nr_type[dtype]

    def get_doc(self):
        return textwrap.dedent(DOC.format(LN = self.longname, T = self.type))

class MathFunctionList:
    def __init__(self, name : str, longname : str, dtype_list : list = []):
        dtype_list = dtype_list if dtype_list else alldtypes
        self.functions = [MathFunction(name, longname, dtype) for dtype in dtype_list]
        self.name = name
        self.longname = longname

    def get_header(self):
        return textwrap.dedent(create_centered_header(self.longname))


def get_doc(math_func : MathFunction):
    return textwrap.dedent(DOC.format(OP = math_func.name, T = math_func.type))

def get_c_templates(f : str):
    with open(f, 'r') as F:
        context = F.read()

    temps = context.split(MAGIC_WORD)
    return {
        "Header" : temps[0],
        "Function" : temps[1],
        "Array" : temps[2],
        "Main" : temps[3]
    }

def get_c_function(template : str, fl : MathFunctionList):
    code = ""
    for f in fl.functions:
        code += f.get_doc()
        code += template.replace("%OP%", f.name)\
                        .replace("%T%", f.type)\
                        .replace("%NT%", f.nr_type)\
                        .replace("%OPC%", f.name.upper())
    return code

def get_c_array(template : str, fl : MathFunctionList):
    all_ = []
    for f in fl.functions:
        all_.append(f"\tNMath_{f.name}_{f.type}")

    code = ",\n".join(all_)
    code = template.replace("%METHODS%", code)\
                    .replace("%OPC%", fl.name.upper())

    return code

def get_c_mainfunction(template : str, fl : MathFunctionList):
    return template.replace("%OP%", fl.name)\
                    .replace("%OPC%", fl.name.upper())

def get_c_code(fl_list : List[MathFunctionList]):
    templates = get_c_templates(SRC_C_FILE)
    
    code = templates['Header']

    f_temp = templates['Function']
    a_temp = templates['Array']
    m_temp = templates['Main']

    for fl in fl_list:
        code += fl.get_header()
        code += get_c_function(f_temp, fl)
        code += get_c_array(a_temp, fl)
        code += get_c_mainfunction(m_temp, fl)

    return code

def get_h_code(fl_list : List[MathFunctionList]):
    with open(SRC_H_FILE, 'r') as f:
        content = f.read().split(MAGIC_WORD)

    tempalte = content[1]

    code = content[0]
    for fl in fl_list:
        code += tempalte.replace("%OP%", fl.name)
    code += content[2]

    return code


def main():
    fl_list = [
        MathFunctionList("Add", "Addition", None),
        MathFunctionList("Mul", "Multiplication", None),
        MathFunctionList("Sub", "Subtraction", None),
        MathFunctionList("Div", "Division", ftypes),
        MathFunctionList("Pow", "Power", None),
        MathFunctionList("Mod", "Module", itypes),
        MathFunctionList("Tdv", "True Division", None),
        MathFunctionList("Bg", "Bigger Then", None),
        MathFunctionList("Bge", "Bigger Then Or Equal", None),
        MathFunctionList("Ls", "Less Then", None),
        MathFunctionList("Lse", "Less Then Or Equal", None),
        MathFunctionList("Eq", "Equal", None),
        MathFunctionList("Neq", "Not Equal", None),
    ]

    code = get_c_code(fl_list)
    cf_path = GEN_DIR
    if not os.path.isdir(cf_path):
        os.mkdir(cf_path)
    cf_file = '__nmath_generated.c'
    cf_path = os.path.join(cf_path, cf_file)
    with open(cf_path, 'w') as f:
        f.write(code)


    code = get_h_code(fl_list)
    hf_path = GEN_DIR
    if not os.path.isdir(hf_path):
        os.mkdir(hf_path)
    gf_file = '__nmath_generated.h'
    hf_path = os.path.join(hf_path, gf_file)
    with open(hf_path, 'w') as f:
        f.write(code)
    
if __name__ == '__main__':
    main()
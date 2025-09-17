# docs/conf.py
# Configuration for Sphinx docs

import os
import sys

sys.path.insert(0, os.path.abspath("../"))  # Make ember importable

# -- Project information -----------------------------------------------------
project = "Ember"
author = "Daniel Hoberman"
release = "0.1.0"

# -- General configuration ---------------------------------------------------
extensions = [
    "sphinx.ext.autodoc",  # Pull in docstrings
    "sphinx.ext.napoleon",  # Google/NumPy style docstrings
    "sphinx.ext.viewcode",  # Link to source code
    "myst_parser",  # Markdown support
]

templates_path = ["_templates"]
exclude_patterns = [
    "_build",
    "tests",
    "src",
    "include",
    "project",
    "cpp_tests",
    "*.md",
    "*.txt",
]

# Support both RST and Markdown
source_suffix = {
    ".rst": "restructuredtext",
    ".md": "markdown",
}

# -- HTML output options -----------------------------------------------------
html_theme = "furo"

html_theme_options = {
    "navigation_with_keys": True,
    "light_logo": "logo_light.png",  # optional
    "dark_logo": "logo_dark.png",  # optional
}

html_static_path = ["_static"]

# Optional: Add custom CSS
# html_css_files = ["custom.css"]

# -- Autodoc options ---------------------------------------------------------
autodoc_typehints = "description"  # Show type hints in description
autodoc_member_order = "bysource"  # Order members as in source code
autodoc_default_flags = ["members", "undoc-members", "show-inheritance"]

# -- Napoleon options (Google/NumPy style) ----------------------------------
napoleon_google_docstring = True
napoleon_numpy_docstring = True
napoleon_include_init_with_doc = True
napoleon_include_private_with_doc = False
napoleon_use_admonition_for_examples = True
napoleon_use_admonition_for_notes = True
napoleon_use_admonition_for_references = True

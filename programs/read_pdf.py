import random
import os
import requests
import flask
# import pdftotext
import pypdf
import tiktoken
import openai
import threading


# Multiple files thread safety
uid_lock = threading.Lock()
uuid = 0

def get_pdf_text(url):
    # Download file
    response = requests.get(url)
    if not response.ok:
        print('response not ok', response.status_code)
        print(response.content)
        return None
    print('Fetched ', url)

    # Save the file
    uid = 0
    global uuid
    with uid_lock:
        uid = uuid
        uuid += 1

    # Write to file and extract text
    # TODO use proper tempfile
    text = ''
    file_path = "/tmp/research_paper." + str(uid) + '.pdf'
    # try:
    #     os.remove(file_path)
    # except Exception:
    #     pass
    with open(file_path, mode="wb+") as file:
        file.write(response.content)
        print('Created temp file ', file_path)
        try:
            # pages = pdftotext.PDF(file)
            reader = pypdf.PdfReader(file)
            pages = reader.pages
            text = '\n'.join([page.extract_text() for page in pages])
            print('Read ' + str(len(pages)) + ' pages')
        except Exception as e:
            print(e)
            return None

    # Fail if too many tokens
    print('Read', str(len(text)), 'chars')
    end_idx = text.rfind('REFERENCES')
    if end_idx == -1:
        end_idx = text.rfind('References')
    text = text[:end_idx] # truncate bibliography and appendix
    tokens = len(tiktoken.encoding_for_model('gpt-4o').encode(text))
    with uid_lock:
        uuid -= 1
    if tokens > 60000:
        print('Too many tokens: ' + str(tokens))
        return 'fat' # too many tokens
    print('Tokens: ' + str(tokens))

    return text



# Server to accept requests
from flask import Flask
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

@app.route('/pdftotext', methods=['GET'])
def ep():
    url = flask.request.args.get('url')
    print(url)
    try:
        return get_pdf_text(url) or 'fail'
    except Exception:
        return 'error'

port_num = 3333
print('starting server on port', str(port_num))
app.run(host="0.0.0.0", port=port_num)


# Should also extract images
# Unfortunately poppler isn't working in Arch rn
'''
import os
import tempfile
from pdf2image import convert_from_path
 
filename = 'target.pdf'
 
with tempfile.TemporaryDirectory() as path:
     images_from_path = convert_from_path(filename, output_folder=path, last_page=1, first_page =0)
 
base_filename  =  os.path.splitext(os.path.basename(filename))[0] + '.jpg'     
 
save_dir = 'your_saved_dir'
 
for page in images_from_path:
    page.save(os.path.join(save_dir, base_filename), 'JPEG')
'''

from .processo_cadastrar_negocio import DocumentoCadastrarNegocio
from app import app
from ....utils.front_helper import *

@app.route('/documento7/novo', methods=['GET', 'POST'])
@login_required
@verifica_permissao
def documento_cadastrar():
   return ProcessoCadastrarNegocio.exibir()

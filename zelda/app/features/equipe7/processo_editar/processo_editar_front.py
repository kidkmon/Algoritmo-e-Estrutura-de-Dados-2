from .processo_editar_negocio import ProcessoEditarNegocio
from app import app
from ...utils.front_helper import *

@app.route('/processo/<processo_id>', methods=['GET', 'POST'])
@login_required
@verifica_permissao
def usuario_editar(processo_id):
    return ProcessoEditarNegocio.exibir(processo_id)
   
# O professor disse que pode entregar até 2h da noite 
# Que era para reunirmos na casa de alguém pra termianr
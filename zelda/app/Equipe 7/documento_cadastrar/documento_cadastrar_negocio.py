from flask import render_template, flash, redirect, url_for
from .documento_cadastrar_form import CadastrarDocumentoForm
from ....cursor import db
from ....utils.flash_errors import flash_errors
from ....tables.equipe7.documento.documento_modelo import Documento
from ....utils.zelda_modelo import ZeldaModelo

class DocumentoCadastrarNegocio:

    def exibir():

        form = CadastrarDocumentoForm()

        if form.validate_on_submit():

            documento = Documento()

            documento.tipo = form.documento_tipo.data
            documento.desc = form.documento_desc.data
            documento.caminho = form.documento_caminho.data
            documento.salva()

            return redirect(url_for('documento_listar'))

        else:
            flash_errors(form)

        return render_template('equipe7_documento_criar.html', form=form)

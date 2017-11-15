from flask import render_template, flash, redirect, url_for
from .documento_editar_form import EditarDocumentoForm
from ....utils.flash_errors import flash_errors
from ....tables.equipe7.documento.documento_modelo import Documento
from ....utils.zelda_modelo import ZeldaModelo


from app import app

class DocumentoEditarNegocio:
    def exibir(documento_id):
        form = EditarDocumentoForm()

        documento = Documento(documento_id)
        if documento.get_id() is None:
            return redirect(url_for('documento_listar'))

        if form.validate_on_submit():
            documento.tipo = form.documento_tipo.data
            documento.desc = form.documento_desc.data
            documento.caminho = form.documento_caminho.data
            documento.salva()

            return redirect(url_for('documento_listar'))

        else:
            flash_errors(form)

        return render_template('equipe7_documento_editar.html', form=form)
